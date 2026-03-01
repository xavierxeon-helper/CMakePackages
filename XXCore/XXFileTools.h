#ifndef XXFileToolsH
#define XXFileToolsH

#include "XXCoreExportDef.h"

#include <QCoreApplication>
#include <QJsonObject>

namespace XX
{
   //! @brief file-related utilities
   //! @ingroup XXCore

   class XXCORE_DECLSPEC FileTools
   {
   public:
      static QJsonObject readJson(const QString& filePath, bool verbose = false);
      static QJsonObject parseBytes(const QByteArray& data);
      static void writeJson(const QJsonObject& data, const QString& filePath, bool verbose = false);

#ifdef Q_OS_WASM
      static QByteArray readIndexDB(const QString& filePath);
      static void writeIndexDB(const QByteArray& data, const QString& filePath);

      static QJsonObject readIndexDBJson(const QString& filePath);
      static void writeIndexDBJson(const QJsonObject& data, const QString& filePath);
#endif // Q_OS_WASM

      static QString compileDropboxPath(const QString& appName = QCoreApplication::applicationName());
      static QString compileNextCloudPath(const QString& appName = QCoreApplication::applicationName());

      static QJsonObject readApiKeys(const QString& appName, bool verbose = false);
      static QStringList compileResourceNames(const QStringList& ignoreList = {":/qt-project.org"});

      static void openVSCode(const QString& path);
      static void openVSCode(QStringList pathList);
   };
} // namespace XX

#endif // NOT XXFileToolsH
