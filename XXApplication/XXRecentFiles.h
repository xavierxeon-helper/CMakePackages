#ifndef XXRecentFilesH
#define XXRecentFilesH

#include "XXApplicationExportDef.h"

#include <QMenu>
#include <QWidget>

namespace XX
{
   class XXAPPLICATION_DECLSPEC RecentFiles
   {
   public:
      using LoadFunction = std::function<void(const QString& fileName)>;

   public:
      RecentFiles(QWidget* parent, const QString& settingsKey, const QString& menuObjectName);

   public:
      void setup(LoadFunction loadFunction, int maxEntries = 10);

      template <typename TargetClass>
      void setup(TargetClass* instance, void (TargetClass::*memberFunction)(const QString&), int maxEntries = 10);

      void clear();
      void add(const QString& fileName);

   private:
      void prepareMenu();

   private:
      const QString settingsKey;
      LoadFunction loadFunction;
      int maxEntries;
      QStringList fileNameList;
      QMenu* menu;
   };
} // namespace XX

#ifndef XXRecentFilesHPP
#include "XXRecentFiles.hpp"
#endif // NOT XXRecentFilesHPP

#endif // NOT XXRecentFilesH
