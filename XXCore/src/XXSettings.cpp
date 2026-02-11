#include "XXSettings.h"

#include <QCoreApplication>
#include <QStandardPaths>

#include <QSettings>

#include <XXFileTools.h>

static const QString ByteArrayMarker = "@ByteArray=";

QString XX::Settings::fileName;

XX::Settings::Settings()
   : data()
{
   if (fileName.isEmpty())
      fileName = compileFileName();

   data = FileTools::readJson(fileName);
}

XX::Settings::~Settings()
{
   FileTools::writeJson(data, fileName);
}

QString XX::Settings::compileFileName()
{
   QString fileName = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
   fileName += "/" + QCoreApplication::organizationName();
   fileName += "/" + QCoreApplication::applicationName() + ".json";

   qDebug() << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
   qDebug() << QCoreApplication::applicationName();
   qDebug() << QCoreApplication::organizationDomain();
   qDebug() << QCoreApplication::organizationName();

   QSettings test;
   qDebug() << test.fileName();
   qDebug() << fileName;

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
   //internal.remove(key);
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
}
