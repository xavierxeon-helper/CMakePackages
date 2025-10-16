#include "RecentFiles.h"

#include <QFileInfo>
#include <QSettings>

RecentFiles::RecentFiles(QWidget* parent, const QString& settingsKey, const QString& menuObjectName)
   : settingsKey(settingsKey)
   , loadFunction()
   , maxEntries(10)
   , fileNameList()
   , menu(nullptr)
{
   QSettings settings;
   fileNameList = settings.value(settingsKey).toStringList();

   menu = new QMenu(parent);
   menu->setObjectName(menuObjectName);

   auto prepareFunction = [this]()
   {
      prepareMenu();
   };
   QObject::connect(menu, &QMenu::aboutToShow, prepareFunction);
}

void RecentFiles::setup(LoadFunction _loadFunction, int _maxEntries)
{
   loadFunction = _loadFunction;
   maxEntries = _maxEntries;
}

void RecentFiles::clear()
{
   fileNameList.clear();

   QSettings settings;
   settings.setValue(settingsKey, fileNameList);
}

void RecentFiles::add(const QString& fileName)
{
   if (fileNameList.contains(fileName))
      return;

   fileNameList.append(fileName);

   while (fileNameList.size() > maxEntries)
      fileNameList.takeFirst();

   QSettings settings;
   settings.setValue(settingsKey, fileNameList);
}

void RecentFiles::prepareMenu()
{
   menu->clear();

   for (const QString& fileName : std::as_const(fileNameList))
   {
      QFileInfo fileInfo(fileName);

      auto loadFileFunction = [this, fileName]()
      {
         if (loadFunction)
            loadFunction(fileName);
      };

      menu->addAction(fileInfo.fileName(), loadFileFunction);
   }

   menu->addSeparator();

   auto clearFunction = [this]()
   {
      clear();
   };

   menu->addAction("Clear", clearFunction);
}
