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

   loadSettings();
}

void Populated::MainWidget::loadSettings()
{
   QSettings settings;
   restoreGeometry(settings.value("MainWidget/Geometry").toByteArray());
}

void Populated::MainWidget::closeEvent(QCloseEvent* ce)
{
   QSettings settings;
   settings.setValue("MainWidget/Geometry", saveGeometry());

   ce->accept();
}

void Populated::MainWidget::placeMenuBar(QMenuBar* menuBar)
{
   Q_UNUSED(menuBar);
   qFatal() << "You must override Populated::MainWidget::placeMenuBar to place the menu bar in your main widget.";
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

   auto createMenu = [&]()
   {
      if (parentMenu)
         return parentMenu->addMenu(text);

      if (!menuBar)
      {
         menuBar = new QMenuBar(this);
         placeMenuBar(menuBar);
      }

      return menuBar->addMenu(text);
   };

   menu = createMenu();
   if (menu)
      menu->setObjectName(objectName);

   return menu;
}
