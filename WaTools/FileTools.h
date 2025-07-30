#ifndef FileToolsH
#define FileToolsH

#include <QCoreApplication>

class FileTools
{
public:
   static QJsonObject readJson(const QString& filePath);
   static QJsonObject parseBytes(const QByteArray& data);
   static void writeJson(const QJsonObject& data, const QString& filePath);
   static QString compileDropboxPath(const QString& appName = QCoreApplication::applicationName());
   static QString compileNextCloudPath(const QString& appName = QCoreApplication::applicationName());
   static QJsonObject readApiKeys(const QString& appName);
   static void printAllResourceNames(const QStringList& ignoreList = {":/qt-project.org"});
};

#ifndef FileToolsHPP
#include "FileTools.hpp"
#endif // NOT FileToolsHPP

#endif // NOT FileToolsH
