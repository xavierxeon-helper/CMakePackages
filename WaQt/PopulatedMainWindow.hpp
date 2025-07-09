#ifndef PopulatedMainWindowHPP
#define PopulatedMainWindowHPP

#include "PopulatedMainWindow.h"

#include <QCloseEvent>
#include <QDockWidget>
#include <QFile>
#include <QFileInfo>
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

inline QString PopulatedMainWindow::writeExampleResource(const QString& xmlResource)
{
   QDomDocument doc;
   QDomElement rootElement = doc.createElement("MenuAndTooBar");
   doc.appendChild(rootElement);

   // toolbar
   QDomElement toolBarElement = doc.createElement("ToolBar");
   toolBarElement.setAttribute("Name", "Main");
   rootElement.appendChild(toolBarElement);

   QDomElement labelElement = doc.createElement("Label");
   labelElement.setAttribute("Text", "Example Label");
   toolBarElement.appendChild(labelElement);

   QDomElement actionElement = doc.createElement("Action");
   actionElement.setAttribute("Name", "Action.Name");
   toolBarElement.appendChild(actionElement);

   QDomElement spacerElement = doc.createElement("Spacer");
   toolBarElement.appendChild(spacerElement);

   QDomElement seperatorElement = doc.createElement("Sperator");
   toolBarElement.appendChild(seperatorElement);

   // menu
   QDomElement menuElement = doc.createElement("Menu");
   menuElement.setAttribute("Name", "Main");
   rootElement.appendChild(menuElement);

   QDomElement actionElement2 = doc.createElement("Action");
   actionElement2.setAttribute("Name", "Action.Name");
   menuElement.appendChild(actionElement2);

   QDomElement subMenuElement = doc.createElement("SubMenu");
   subMenuElement.setAttribute("Name", "SubMenu");
   menuElement.appendChild(subMenuElement);

   QDomElement actionElement3 = doc.createElement("Action");
   actionElement3.setAttribute("Name", "Action.Name");
   subMenuElement.appendChild(actionElement3);

   QDomElement seperatorElement2 = doc.createElement("Sperator");
   menuElement.appendChild(seperatorElement2);

   QDomElement subMenuElement2 = doc.createElement("Menu");
   subMenuElement2.setAttribute("Name", "DynamicMenu.Name");
   menuElement.appendChild(subMenuElement2);

   QFile file(xmlResource);
   if (!file.open(QIODevice::WriteOnly))
      return QString();

   file.write(doc.toByteArray(3));
   file.close();

   QFileInfo info(file.fileName());
   return info.absoluteFilePath();
}

inline QAction* PopulatedMainWindow::addAction(QIcon icon, QString text, QString objectName, QObject* instance, auto slotFunction)
{
   QAction* action = new QAction(icon, text, instance);
   action->setObjectName(objectName);
   connect(action, &QAction::triggered, instance, slotFunction);

   return action;
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

inline void PopulatedMainWindow::addDockWidget(QWidget* widget, const Qt::DockWidgetArea& area)
{
   QDockWidget* dockWidget = new QDockWidget(this);
   dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
   dockWidget->setTitleBarWidget(new QWidget());

   dockWidget->setWidget(widget);
   QMainWindow::addDockWidget(area, dockWidget);
}

inline void PopulatedMainWindow::closeEvent(QCloseEvent* ce)
{
   QSettings settings;
   settings.setValue("MainWidget/Geometry", saveGeometry());
   settings.setValue("MainWidget/State", saveState());

   ce->accept();
}

inline QMenu* PopulatedMainWindow::createPopupMenu()
{
   return nullptr;
}

inline void PopulatedMainWindow::createToolBar(QDomElement thingElement)
{
   auto findOrCreateToolBar = [&](const QString& name)
   {
      QToolBar* toolBar = findChild<QToolBar*>(name, Qt::FindChildrenRecursively);
      if (toolBar)
         return toolBar;

      toolBar = addToolBar(name);
      toolBar->setObjectName(name);
      toolBar->setMovable(false);
      toolBar->setIconSize(QSize(24, 24));

      return toolBar;
   };

   const QString name = thingElement.attribute("Name");
   QToolBar* toolBar = findOrCreateToolBar(name);

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
