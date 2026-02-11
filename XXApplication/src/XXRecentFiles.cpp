#include "XXRecentFiles.h"

#include <QFileInfo>

#include <XXSettings.h>

XX::RecentFiles::RecentFiles(QWidget* parent, const QString& settingsKey, const QString& menuObjectName)
   : settingsKey(settingsKey)
   , loadFunction()
   , maxEntries(10)
   , fileNameList()
   , menu(nullptr)
{
   XX::Settings settings;
   fileNameList = settings.value(settingsKey).toStringList();

   menu = new QMenu(parent);
   menu->setObjectName(menuObjectName);

   auto prepareFunction = [this]()
   {
      prepareMenu();
   };
   QObject::connect(menu, &QMenu::aboutToShow, prepareFunction);
}

void XX::RecentFiles::setup(LoadFunction _loadFunction, int _maxEntries)
{
   loadFunction = _loadFunction;
   maxEntries = _maxEntries;
}

void XX::RecentFiles::clear()
{
   fileNameList.clear();

   XX::Settings settings;
   settings.setValue(settingsKey, fileNameList);
}

void XX::RecentFiles::add(const QString& fileName)
{
   if (fileNameList.contains(fileName))
      return;

   fileNameList.append(fileName);

   while (fileNameList.size() > maxEntries)
      fileNameList.takeFirst();

   XX::Settings settings;
   settings.setValue(settingsKey, fileNameList);
}

void XX::RecentFiles::prepareMenu()
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
