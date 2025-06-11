#ifndef FileToolsH
#define FileToolsH

#include <QCoreApplication>

class FileTools
{
public:
   static QString compileDropboxPath(const QString& appName = QCoreApplication::applicationName());
   static QString compileNextCloudPath(const QString& appName = QCoreApplication::applicationName());
};

#ifndef FileToolsHPP
#include "FileTools.hpp"
#endif // NOT FileToolsHPP

#endif // NOT FileToolsH
