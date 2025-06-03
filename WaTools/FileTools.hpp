#ifndef FileToolsHPP
#define FileToolsHPP

#include "FileTools.h"

#include <QJsonDocument>
#include <QJsonObject>

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

#endif // NOT FileToolsHPP
