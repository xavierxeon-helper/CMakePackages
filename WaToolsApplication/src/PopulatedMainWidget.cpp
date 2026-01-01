#include "PopulatedMainWidget.h"

#include <QCloseEvent>
#include <QMenu>
#include <QSettings>

Populated::MainWidget::MainWidget()
   : QWidget(nullptr)
   , Abstract(this)
   , Singleton<MainWidget>()
   , menuBar(nullptr)
{
   ToolBarCreationFunction toolBarCreationFunction = std::bind(&MainWidget::findOrCreateToolBar, this, std::placeholders::_1);
   MenuCreationFunction menuCreationFunction = std::bind(&MainWidget::findOrCreateMenu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   setFunctions(toolBarCreationFunction, menuCreationFunction);

   QSettings settings;
   restoreGeometry(settings.value("MainWidget/Geometry").toByteArray());
}

void Populated::MainWidget::closeEvent(QCloseEvent* ce)
{
   QSettings settings;
   settings.setValue("MainWidget/Geometry", saveGeometry());

   ce->accept();
}

QToolBar* Populated::MainWidget::findOrCreateToolBar(const QString& objectName)
{
   QToolBar* toolBar = findChild<QToolBar*>(objectName, Qt::FindChildrenRecursively);
   return toolBar;
}

QMenu* Populated::MainWidget::findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu)
{
   QMenu* menu = findChild<QMenu*>(objectName, Qt::FindChildrenRecursively);
   if (menu)
   {
      if (parentMenu)
      {
         menu->setTitle(text);
         parentMenu->addMenu(menu);
      }
      return menu;
   }

   menu = parentMenu ? parentMenu->addMenu(text) : (menuBar ? menuBar->addMenu(text) : nullptr);
   menu->setObjectName(objectName);
   return menu;
}
