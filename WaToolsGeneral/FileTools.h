#ifndef FileToolsH
#define FileToolsH

#include <QCoreApplication>
#include <QJsonObject>

class FileTools
{
public:
   static QJsonObject readJson(const QString& filePath);
   static QJsonObject parseBytes(const QByteArray& data);
   static void writeJson(const QJsonObject& data, const QString& filePath);
   static QString compileDropboxPath(const QString& appName = QCoreApplication::applicationName());
   static QString compileNextCloudPath(const QString& appName = QCoreApplication::applicationName());
   static QJsonObject readApiKeys(const QString& appName);
   static QStringList compileResourceNames(const QStringList& ignoreList = {":/qt-project.org"});
};

#endif // NOT FileToolsH
