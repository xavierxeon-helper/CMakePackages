#include "XXSettings.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

#include <QSettings>

#include <XXFileTools.h>

QString XX::Settings::fileName;
QJsonObject XX::Settings::data;
int XX::Settings::instanceCount = 0;
bool XX::Settings::modified = false;

const QString XX::Settings::ByteArrayMarker = "@ByteArray=";

XX::Settings::Settings()
{
   if (fileName.isEmpty())
      fileName = compileFileName();

   if (0 == instanceCount)
      data = FileTools::readJson(fileName);
   instanceCount++;
}

XX::Settings::~Settings()
{
   instanceCount--;
   if (0 == instanceCount && modified)
   {
      FileTools::writeJson(data, fileName);
      modified = false;
   }
}

QString XX::Settings::compileFileName()
{
#if defined(Q_OS_MAC)
   QString fileName = QDir::homePath() + "/.config";
   fileName += "/" + QCoreApplication::organizationDomain();
   fileName += "/" + QCoreApplication::applicationName() + ".json";
#elif defined(Q_OS_WINDOWS)
   QString fileName = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
   fileName += "/" + QCoreApplication::organizationName();
   fileName += "/" + QCoreApplication::applicationName() + ".json";
#else
   QString fileName = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
   fileName += "/" + QCoreApplication::organizationName();
   fileName += "/" + QCoreApplication::applicationName() + ".json";
#endif

   return fileName;
}

void XX::Settings::setValue(const QString& key, const QVariant& value)
{
   const PathKey pathKey = compilePathKey(key);

   switch (value.typeId())
   {
      case QMetaType::Type::QByteArray:
      {
         const QByteArray encodedValue = value.toByteArray().toBase64();
         setPathValue(pathKey, ByteArrayMarker + QString::fromUtf8(encodedValue));
         break;
      }
      default:
      {
         setPathValue(pathKey, QJsonValue::fromVariant(value));
         break;
      }
   }
}

QVariant XX::Settings::value(const QString& key, const QVariant& defaultValue) const
{
   const PathKey pathKey = compilePathKey(key);
   const QJsonValue value = getPathValue(pathKey);
   if (value.isUndefined())
      return defaultValue;

   switch (value.type())
   {
      case QJsonValue::String:
      {
         QString text = value.toString();
         if (text.startsWith(ByteArrayMarker))
         {
            const QByteArray encodedValue = text.mid(ByteArrayMarker.size()).toUtf8();
            return QByteArray::fromBase64(encodedValue);
         }
         else
            return text;
      }
      default:
         return value.toVariant();
   }

   return QVariant();
}

void XX::Settings::clearValue(const QString& key)
{
   const PathKey pathKey = compilePathKey(key);
   clearPath(pathKey);
}

void XX::Settings::setJsonValue(const QString& key, const QJsonValue& value)
{
   const PathKey pathKey = compilePathKey(key);
   setPathValue(pathKey, value);
}

QJsonValue XX::Settings::jsonValue(const QString& key) const
{
   const PathKey pathKey = compilePathKey(key);
   const QJsonValue value = getPathValue(pathKey);

   return value;
}

XX::Settings::PathKey XX::Settings::compilePathKey(const QString& key) const
{
   QStringList path = key.split("/");
   if (1 == path.size())
      path.prepend("General");

   PathKey pathKey;
   pathKey.key = path.takeLast();
   pathKey.path = path;

   return pathKey;
}

QJsonValue XX::Settings::getPathValue(const PathKey& pathKey) const
{
   using InternalFunction = std::function<QJsonValue(const QJsonObject&, QStringList)>;
   InternalFunction getInternal = [&](const QJsonObject& parent, QStringList path)
   {
      if (path.isEmpty())
      {
         return parent[pathKey.key];
      }
      else
      {
         const QString key = path.takeFirst();
         const QJsonObject content = parent[key].toObject();

         return getInternal(content, path);
      }
   };

   const QJsonValue value = getInternal(data, pathKey.path);
   return value;
}

void XX::Settings::setPathValue(const PathKey& pathKey, const QJsonValue& value)
{
   using InternalFunction = std::function<void(QJsonObject&, QStringList)>;
   InternalFunction setInternal = [&](QJsonObject& parent, QStringList path)
   {
      if (path.isEmpty())
      {
         parent[pathKey.key] = value;
      }
      else
      {
         const QString key = path.takeFirst();
         QJsonObject content = parent[key].toObject();

         setInternal(content, path);
         parent[key] = content;
      }
   };

   setInternal(data, pathKey.path);
   modified = true;
}

void XX::Settings::clearPath(const PathKey& pathKey)
{
   using InternalFunction = std::function<void(QJsonObject&, QStringList)>;
   InternalFunction clearInternal = [&](QJsonObject& parent, QStringList path)
   {
      if (path.isEmpty())
      {
         parent.remove(pathKey.key);
      }
      else
      {
         const QString key = path.takeFirst();
         QJsonObject content = parent[key].toObject();

         clearInternal(content, path);
         parent[key] = content;
      }
   };

   clearInternal(data, pathKey.path);
   modified = true;
}
