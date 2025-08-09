#include "ActionPopulation.h"

#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QMenu>

ActionPopulation::ActionPopulation(QWidget* parentWidget, ToolBarCreationFunction toolBarCreationFunction, MenuCreationFunction menuCreationFunction)
   : QObject(parentWidget)
   , parentWidget(parentWidget)
   , toolBarCreationFunction(toolBarCreationFunction)
   , menuCreationFunction(menuCreationFunction)
{
}

QString ActionPopulation::writeExampleResource(const QString& xmlResource)
{
   QDomDocument doc;
   QDomElement rootElement = doc.createElement("MenuAndTooBar");
   doc.appendChild(rootElement);

   // toolbar
   QDomElement toolBarElement = doc.createElement("ToolBar");
   toolBarElement.setAttribute("ObjectName", "Main");
   rootElement.appendChild(toolBarElement);

   QDomElement labelElement = doc.createElement("Label");
   labelElement.setAttribute("Text", "Example Label");
   toolBarElement.appendChild(labelElement);

   QDomElement actionElement = doc.createElement("Action");
   actionElement.setAttribute("ObjectName", "Action.Name");
   toolBarElement.appendChild(actionElement);

   QDomElement seperatorElement = doc.createElement("Separator");
   toolBarElement.appendChild(seperatorElement);

   QDomElement spacerElement = doc.createElement("Spacer");
   toolBarElement.appendChild(spacerElement);

   // menu
   QDomElement menuElement = doc.createElement("Menu");
   menuElement.setAttribute("ObjectName", "Main");
   menuElement.setAttribute("Text", "Main");
   rootElement.appendChild(menuElement);

   QDomElement actionElement2 = doc.createElement("Action");
   actionElement2.setAttribute("ObjectName", "Action.Name");
   menuElement.appendChild(actionElement2);

   QDomElement subMenuElement = doc.createElement("Menu");
   subMenuElement.setAttribute("ObjectName", "Menu");
   subMenuElement.setAttribute("Text", "SubMenu");
   menuElement.appendChild(subMenuElement);

   QDomElement actionElement3 = doc.createElement("Action");
   actionElement3.setAttribute("ObjectName", "Action.Name");
   subMenuElement.appendChild(actionElement3);

   QDomElement seperatorElement2 = doc.createElement("Separator");
   menuElement.appendChild(seperatorElement2);

   QDomElement subMenuElement2 = doc.createElement("Menu");
   subMenuElement2.setAttribute("ObjectName", "DynamicMenu.Name");
   menuElement.appendChild(subMenuElement2);

   QFile file(xmlResource);
   if (!file.open(QIODevice::WriteOnly))
      return QString();

   file.write(doc.toByteArray(3));
   file.close();

   QFileInfo info(file.fileName());
   return info.absoluteFilePath();
}

void ActionPopulation::populateMenuAndToolBar(const QString& xmlResource)
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

void ActionPopulation::createToolBar(QDomElement thingElement)
{
   if (!toolBarCreationFunction)
      return;

   const QString objectName = thingElement.attribute("ObjectName");
   QToolBar* toolBar = toolBarCreationFunction(objectName);

   for (QDomElement contentElement = thingElement.firstChildElement(); !contentElement.isNull(); contentElement = contentElement.nextSiblingElement())
   {
      const QString what = contentElement.tagName();
      if ("Action" == what)
      {
         const QString objectName = contentElement.attribute("ObjectName");
         QAction* action = parentWidget->findChild<QAction*>(objectName, Qt::FindChildrenRecursively);
         if (action)
            toolBar->addAction(action);
         else
            qWarning() << __FUNCTION__ << "action not found" << objectName;
      }
      else if ("Separator" == what)
      {
         toolBar->addSeparator();
      }
      else if ("Spacer" == what)
      {
         QWidget* widget = new QWidget(parentWidget);
         widget->setMinimumWidth(100);
         widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
         toolBar->addWidget(widget);
      }
      else if ("Label" == what)
      {
         const QString text = contentElement.attribute("Text");
         QLabel* label = new QLabel(text, parentWidget);
         label->setMargin(5);
         toolBar->addWidget(label);
      }
      else if ("Widget" == what)
      {
         const QString objectName = contentElement.attribute("ObjectName");
         QWidget* widget = parentWidget->findChild<QWidget*>(objectName, Qt::FindChildrenRecursively);
         if (widget)
            toolBar->addWidget(widget);
         else
            qWarning() << __FUNCTION__ << "widget not found" << objectName;
      }
   }
}

void ActionPopulation::createMenu(QDomElement thingElement, QMenu* parentMenu)
{
   if (!menuCreationFunction)
      return;

   const QString objectName = thingElement.attribute("ObjectName");
   const QString text = thingElement.attribute("Text");
   QMenu* menu = menuCreationFunction(objectName, text, parentMenu);

   for (QDomElement contentElement = thingElement.firstChildElement(); !contentElement.isNull(); contentElement = contentElement.nextSiblingElement())
   {
      const QString what = contentElement.tagName();
      if ("Action" == what)
      {
         const QString name = contentElement.attribute("ObjectName");
         QAction* action = parentWidget->findChild<QAction*>(name, Qt::FindChildrenRecursively);
         if (action)
            menu->addAction(action);
         else
            qWarning() << __FUNCTION__ << "action not found" << objectName;
      }
      else if ("Separator" == what)
      {
         menu->addSeparator();
      }
      else if ("Menu" == what)
      {
         createMenu(contentElement, menu);
      }
   }
}
