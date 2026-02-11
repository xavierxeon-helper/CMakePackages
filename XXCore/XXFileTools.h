#ifndef XXFileToolsH
#define XXFileToolsH

#include "XXCoreExportDef.h"

#include <QCoreApplication>
#include <QJsonObject>

namespace XX
{
   class XXCORE_DECLSPEC FileTools
   {
   public:
      static QJsonObject readJson(const QString& filePath, bool verbose = false);
      static QJsonObject parseBytes(const QByteArray& data);
      static void writeJson(const QJsonObject& data, const QString& filePath, bool verbose = false);
      static QString compileDropboxPath(const QString& appName = QCoreApplication::applicationName());
      static QString compileNextCloudPath(const QString& appName = QCoreApplication::applicationName());
      static QJsonObject readApiKeys(const QString& appName, bool verbose = false);
      static QStringList compileResourceNames(const QStringList& ignoreList = {":/qt-project.org"});
   };
} // namespace XX

#endif // NOT XXFileToolsH
