#ifndef FileToolsHPP
#define FileToolsHPP

#include "FileTools.h"

#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QStandardPaths>

inline QJsonObject FileTools::readJson(const QString& filePath)
{
   QFile file(filePath);
   if (!file.open(QIODevice::ReadOnly))
      return QJsonObject();

   const QByteArray fileContent = file.readAll();
   file.close();

   return parseBytes(fileContent);

}

inline QJsonObject FileTools::parseBytes(const QByteArray& data)
{

   QJsonParseError parseError;
   QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

   if (QJsonParseError::NoError != parseError.error)
   {
      qWarning() << "Failed to parse JSON file:" << parseError.errorString();
      return QJsonObject();
   }

   const QJsonObject object = doc.object();
   return object;
}

inline void FileTools::writeJson(const QJsonObject& data, const QString& filePath)
{
   if (data.isEmpty())
      return;

   QFile file(filePath);
   if (!file.open(QIODevice::WriteOnly))
      return;

   QJsonDocument doc(data);
   file.write(doc.toJson(QJsonDocument::Indented));
   file.close();
}

inline QString FileTools::compileDropboxPath(const QString& appName)
{
#if defined(Q_OS_WIN32)
   QString homePath = QDir::homePath();
   homePath = QDir::fromNativeSeparators(homePath);
   QString dropboxInfoPath = homePath + "/AppData/Local/Dropbox/info.json";
#elif defined(Q_OS_MACOS)
   QString dropboxInfoPath = QDir::homePath() + "/.dropbox/info.json";
#else // linux
   QString dropboxInfoPath = QDir::homePath() + "/.dropbox/info.json";
#endif

   const QJsonObject dropoxObject = readJson(dropboxInfoPath);
   if (dropoxObject.isEmpty())
      return QString();

   QJsonValue jsonPersonal = dropoxObject.value("personal");
   if (jsonPersonal.isUndefined())
      return QString();

   QJsonValue jsonPath = jsonPersonal.toObject().value("path");
   if (jsonPath.isUndefined())
      return QString();

   QString dropBoxPath = jsonPath.toString();
   dropBoxPath = QDir::fromNativeSeparators(dropBoxPath);
   QString path = dropBoxPath + QString("/Apps/") + appName;

   return path;
}

inline QString FileTools::compileNextCloudPath(const QString& appName)
{
   /*
   On Linux distributions:
$HOME/.config/Nextcloud/nextcloud.cfg
On Microsoft Windows systems:
%APPDATA%\Nextcloud\nextcloud.cfg
On macOS systems:
$HOME/Library/Preferences/Nextcloud/nextcloud.cfg
*/

#if defined(Q_OS_WIN32)
   QString appPath = QStandardPaths ::writableLocation(QStandardPaths::AppDataLocation);
   appPath = QDir::fromNativeSeparators(appPath);
   appPath.replace(QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName(), "");
   const QString nextCloudConfPath = appPath + "/Nextcloud/nextcloud.cfg";
#elif defined(Q_OS_MACOS)
   const QString nextCloudConfPath = QDir::homePath() + "/Library/Preferences/Nextcloud/nextcloud.cfg";
#else // linux
   const QString nextCloudConfPath = QDir::homePath() + "/.config/Nextcloud/nextcloud.cfg";
#endif

   if (!QFile::exists(nextCloudConfPath))
      return QString();

   QSettings settings(nextCloudConfPath, QSettings::IniFormat);

   QString nextCloudPath = settings.value("Accounts/0/Folders/1/localPath").toString();
   nextCloudPath = QDir::fromNativeSeparators(nextCloudPath);
   QString path = nextCloudPath + QString("Apps/") + appName;

   return path;
}

inline QJsonObject FileTools::readApiKeys(const QString& appName)
{
   static const QStringList homePaths = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
   const QString keyFileName = homePaths.first() + "/.ApiKeys/" + appName + ".json";

   return readJson(keyFileName);
}


inline void FileTools::printAllResourceNames(const QStringList& ignoreList)
{
   auto ignoreName = [&](const QString& name)
   {
      for(const QString& test: ignoreList)
      {
         if(name.startsWith(test))
            return true;
      }
      return false;
   };

   QDirIterator it(":", QDirIterator::Subdirectories);
   while (it.hasNext())
   {
      const QString name = it.next();
      if(ignoreName(name))
         continue;
      qDebug() << name;
   }
}

#endif // NOT FileToolsHPP
