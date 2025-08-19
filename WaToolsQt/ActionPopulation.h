#ifndef ActionPopulationH
#define ActionPopulationH

#include "WaToolsQtExportDef.h"
#include <QObject>

#include <QDomElement>
#include <QToolBar>

class WATOOLS_QT_DECLSPEC ActionPopulation : public QObject
{
   Q_OBJECT

public:
   using ToolBarCreationFunction = std::function<QToolBar*(const QString& objectName)>;
   using MenuCreationFunction = std::function<QMenu*(const QString& objectName, const QString& text, QMenu* parentMenu)>;

public:
   ActionPopulation(QWidget* parentWidget, ToolBarCreationFunction toolBarCreationFunction, MenuCreationFunction menuCreationFunction);

public:
   static QString writeExampleResource(const QString& xmlResource);
   void populateMenuAndToolBar(const QString& xmlResource);

private:
   void createToolBar(QDomElement thingElement);
   void createMenu(QDomElement thingElement, QMenu* parentMenu);

private:
   QWidget* parentWidget;
   ToolBarCreationFunction toolBarCreationFunction;
   MenuCreationFunction menuCreationFunction;
};

#endif // NOT ActionPopulationH
