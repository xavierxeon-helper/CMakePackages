#include "PopulatedMainWindow.h"

#include <QCloseEvent>
#include <QDir>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>

PopulatedMainWindow* PopulatedMainWindow::me = nullptr;

PopulatedMainWindow::PopulatedMainWindow()
   : QMainWindow(nullptr)
   , actionPopulation(nullptr)
{
   me = this;

   ActionPopulation::ToolBarCreationFunction toolBarCreationFunction = std::bind(&PopulatedMainWindow::findOrCreateToolBar, this, std::placeholders::_1);
   ActionPopulation::MenuCreationFunction menuCreationFunction = std::bind(&PopulatedMainWindow::findOrCreateMenu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   actionPopulation = new ActionPopulation(this, toolBarCreationFunction, menuCreationFunction);

   QSettings settings;
   restoreGeometry(settings.value("MainWidget/Geometry").toByteArray());
   restoreState(settings.value("MainWidget/State").toByteArray());
}

PopulatedMainWindow::~PopulatedMainWindow()
{
   me = nullptr;
}

PopulatedMainWindow* PopulatedMainWindow::the()
{
   return me;
}

void PopulatedMainWindow::printSettingsLocation()
{
   QSettings settings;
   const QString fileName = QDir::toNativeSeparators(settings.fileName());

   qInfo() << "SETTINGS @" << qPrintable(fileName);
}

void PopulatedMainWindow::populateMenuAndToolBar(const QString& xmlResource)
{
   actionPopulation->populateMenuAndToolBar(xmlResource);
}

QDockWidget* PopulatedMainWindow::addDockWidget(QWidget* widget, const Qt::DockWidgetArea& area)
{
   QDockWidget* dockWidget = new QDockWidget(this);
   dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
   dockWidget->setTitleBarWidget(new QWidget());

   dockWidget->setWidget(widget);
   QMainWindow::addDockWidget(area, dockWidget);

   static int dockWidgetCounter = 0;
   dockWidgetCounter++;
   dockWidget->setObjectName(QString("DockWidget_%1").arg(dockWidgetCounter));

   return dockWidget;
}

void PopulatedMainWindow::closeEvent(QCloseEvent* ce)
{
   saveWindowSettings();
   ce->accept();
}

QMenu* PopulatedMainWindow::createPopupMenu()
{
   return nullptr;
}

void PopulatedMainWindow::saveWindowSettings()
{
   QSettings settings;
   settings.setValue("MainWidget/Geometry", saveGeometry());
   settings.setValue("MainWidget/State", saveState());
}

QToolBar* PopulatedMainWindow::findOrCreateToolBar(const QString& objectName)
{
   QToolBar* toolBar = findChild<QToolBar*>(objectName, Qt::FindChildrenRecursively);
   if (toolBar)
      return toolBar;

   toolBar = addToolBar(objectName);
   toolBar->setObjectName(objectName);
   toolBar->setMovable(false);
   toolBar->setIconSize(QSize(24, 24));

   return toolBar;
}

QMenu* PopulatedMainWindow::findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu)
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

   menu = parentMenu ? parentMenu->addMenu(text) : menuBar()->addMenu(text);
   menu->setObjectName(objectName);
   return menu;
}
