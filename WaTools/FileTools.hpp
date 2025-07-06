#ifndef FileToolsHPP
#define FileToolsHPP

#include "FileTools.h"

#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QStandardPaths>

inline QString FileTools::compileDropboxPath(const QString& appName)
{
#if defined(Q_OS_WIN32)
   QString homePath = QDir::homePath();
   homePath = QDir::fromNativeSeparators(homePath);
   QString dropboxInfoPath = homePath + "/AppData/Local/Dropbox/info.json";
#elif defined(Q_OS_OSX)
   QString dropboxInfoPath = QDir::homePath() + "/.dropbox/info.json";
#else // linux
   QString dropboxInfoPath = QDir::homePath() + "/.dropbox/info.json";
#endif

   QFile dropboxInfo(dropboxInfoPath);
   if (!dropboxInfo.open(QIODevice::ReadOnly))
      return QString();

   QByteArray data = dropboxInfo.readAll();
   dropboxInfo.close();

   QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
   if (!jsonDoc.isObject())
      return QString();

   QJsonValue jsonPersonal = jsonDoc.object().value("personal");
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
#elif defined(Q_OS_OSX)
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

   QFile file(keyFileName);
   if (!file.open(QIODevice::ReadOnly))
      return QJsonObject();

   const QByteArray fileContent = file.readAll();
   file.close();

   QJsonParseError error;
   QJsonDocument doc = QJsonDocument::fromJson(fileContent, &error);

   if (QJsonParseError::NoError != error.error)
      return QJsonObject();

   const QJsonObject keysObject = doc.object();
   return keysObject;
}

#endif // NOT FileToolsHPP
