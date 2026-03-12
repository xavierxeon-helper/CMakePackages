#include "XXIndexedDB.h"

#include <QDirIterator>

#ifdef Q_OS_WASM
#include <emscripten.h>
#include <emscripten/bind.h>

// clang-format off
EM_ASYNC_JS(
   void,
   initIndexedDBFileSystem,
   (const char* str),
   {
      let path = UTF8ToString(str);

      FS.mkdir(path);
      FS.mount(IDBFS, {autoPersist: true }, path);


      FS.isReady = false;
      function init(resolve, reject)
      {
         function syncCallback(error)
         {
            console.log("SYNC", error);
            FS.isReady = true;
            resolve();
         }

         FS.syncfs(true, syncCallback);
      }

      await new Promise(init);
   }
);

EM_JS(
   bool,
   indexedDBSystemReady,
   (),
   {
      return FS.isReady;
   }
);
// clang-format on

#endif // Q_OS_WASM


void XX::IndexedDB::initFileSystem(bool printContent, const QString& basePath)
{
#ifdef Q_OS_WASM
   initIndexedDBFileSystem(basePath.toUtf8().constData());

   if (!printContent)
      return;

   QDirIterator it(basePath, QDirIterator::Subdirectories);
   while (it.hasNext())
   {
      const QString name = it.next();
      qDebug() << "INDEX DB" << name;
   }

#endif // Q_OS_WASM
}

bool XX::IndexedDB::checkFileSystem()
{
#ifdef Q_OS_WASM
   return indexedDBSystemReady();
#else
   return true;
#endif // Q_OS_WASM
}
