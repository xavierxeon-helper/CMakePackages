#ifndef PopulatedMainWindowHPP
#define PopulatedMainWindowHPP

#include "PopulatedMainWindow.h"

#include <QCloseEvent>
#include <QFile>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QToolBar>

inline PopulatedMainWindow* PopulatedMainWindow::me = nullptr;

inline PopulatedMainWindow::PopulatedMainWindow()
   : QMainWindow(nullptr)
{
   me = this;
   QSettings settings;
   restoreGeometry(settings.value("MainWidget/Geometry").toByteArray());
   restoreState(settings.value("MainWidget/State").toByteArray());
}

inline PopulatedMainWindow::~PopulatedMainWindow()
{
   me = nullptr;
}

inline PopulatedMainWindow* PopulatedMainWindow::the()
{
   return me;
}


inline void PopulatedMainWindow::printSettingsLocation()
{
   QSettings settings;
   qInfo() << "SETTINGS @" << settings.fileName();

}

inline void PopulatedMainWindow::populateMenuAndToolBar(const QString& xmlResource)
{
   QFile file(xmlResource);
   if (!file.open(QIODevice::ReadOnly))
      return;

   const QByteArray content = file.readAll();
   file.close();

   QDomDocument doc;
   QDomDocument::ParseResult result = doc.setContent(content);
   if (!result.errorMessage.isEmpty())
   {
      qWarning() << "unable to read xml" << result.errorMessage;
      return;
   }

   const QDomElement rootElement = doc.documentElement();
   for (QDomElement thingElement = rootElement.firstChildElement(); !thingElement.isNull(); thingElement = thingElement.nextSiblingElement())
   {
      const QString what = thingElement.tagName();
      if ("ToolBar" == what)
         createToolBar(thingElement);
      else if ("Menu" == what)
         createMenu(thingElement, nullptr);
   }
}

inline void PopulatedMainWindow::closeEvent(QCloseEvent* ce)
{
   QSettings settings;
   settings.setValue("MainWidget/Geometry", saveGeometry());
   settings.setValue("MainWidget/State", saveState());

   ce->accept();
}

inline void PopulatedMainWindow::createToolBar(QDomElement thingElement)
{
   const QString name = thingElement.attribute("Name");
   QToolBar* toolBar = addToolBar(name);
   toolBar->setObjectName(name);
   toolBar->setMovable(false);
   toolBar->setIconSize(QSize(24, 24));

   for (QDomElement contentElement = thingElement.firstChildElement(); !contentElement.isNull(); contentElement = contentElement.nextSiblingElement())
   {
      const QString what = contentElement.tagName();
      if ("Action" == what)
      {
         const QString name = contentElement.attribute("Name");
         QAction* action = findChild<QAction*>(name, Qt::FindChildrenRecursively);
         if (action)
            toolBar->addAction(action);
      }
      else if ("Sperator" == what)
      {
         toolBar->addSeparator();
      }
      else if ("Spacer" == what)
      {
         QWidget* widget = new QWidget(this);
         widget->setMinimumWidth(100);
         widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
         toolBar->addWidget(widget);
      }
      else if ("Label" == what)
      {
         const QString text = contentElement.attribute("Text");
         QLabel* label = new QLabel(text, this);
         label->setMargin(5);
         toolBar->addWidget(label);
      }
   }
}

inline void PopulatedMainWindow::createMenu(QDomElement thingElement, QMenu* parentMenu)
{
   const QString name = thingElement.attribute("Name");
   QMenu* menu = parentMenu ? parentMenu->addMenu(name) : menuBar()->addMenu(name);

   for (QDomElement contentElement = thingElement.firstChildElement(); !contentElement.isNull(); contentElement = contentElement.nextSiblingElement())
   {
      const QString what = contentElement.tagName();
      if ("Action" == what)
      {
         const QString name = contentElement.attribute("Name");
         QAction* action = findChild<QAction*>(name, Qt::FindChildrenRecursively);
         if (action)
            menu->addAction(action);
      }
      else if ("Sperator" == what)
      {
         menu->addSeparator();
      }
      else if ("Menu" == what)
      {
         const QString name = contentElement.attribute("Name");
         QMenu* subMenu = findChild<QMenu*>(name, Qt::FindChildrenRecursively);
         if (subMenu)
            menu->addMenu(subMenu);
      }
      else if ("SubMenu" == what)
      {
         createMenu(contentElement, menu);
      }
   }
}

#endif // NOT PopulatedMainWindowHPP
