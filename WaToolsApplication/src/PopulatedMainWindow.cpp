#include "PopulatedMainWindow.h"

#include <QCloseEvent>
#include <QDir>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>

Populated::MainWindow* Populated::MainWindow::me = nullptr;

Populated::MainWindow::MainWindow()
   : QMainWindow(nullptr)
   , Abstract(this)
{
   me = this;

   ToolBarCreationFunction toolBarCreationFunction = std::bind(&Populated::MainWindow::findOrCreateToolBar, this, std::placeholders::_1);
   MenuCreationFunction menuCreationFunction = std::bind(&Populated::MainWindow::findOrCreateMenu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   setFunctions(toolBarCreationFunction, menuCreationFunction);

   QSettings settings;
   restoreGeometry(settings.value("MainWindow/Geometry").toByteArray());
   restoreState(settings.value("MainWindow/State").toByteArray());
}

Populated::MainWindow::~MainWindow()
{
   me = nullptr;
}

Populated::MainWindow* Populated::MainWindow::the()
{
   return me;
}

QDockWidget* Populated::MainWindow::addDockWidget(QWidget* widget, const Qt::DockWidgetArea& area)
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

void Populated::MainWindow::closeEvent(QCloseEvent* ce)
{
   saveWindowSettings();
   ce->accept();
}

QMenu* Populated::MainWindow::createPopupMenu()
{
   return nullptr;
}

void Populated::MainWindow::saveWindowSettings()
{
   QSettings settings;
   settings.setValue("MainWindow/Geometry", saveGeometry());
   settings.setValue("MainWindow/State", saveState());
}

QToolBar* Populated::MainWindow::findOrCreateToolBar(const QString& objectName)
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

QMenu* Populated::MainWindow::findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu)
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
