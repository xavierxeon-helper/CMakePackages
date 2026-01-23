#ifndef PopulatedAbstractH
#define PopulatedAbstractH

#include "WaToolsApplicationExportDef.h"

#include <QDomElement>
#include <QToolBar>
#include <QWidget>

namespace Populated
{
   class WATOOLSAPPLICATION_DECLSPEC Abstract
   {
   public:
      using ToolBarCreationFunction = std::function<QToolBar*(const QString& objectName)>;
      using MenuCreationFunction = std::function<QMenu*(const QString& objectName, const QString& text, QMenu* parentMenu)>;

   public:
      Abstract(QWidget* parentWidget);
      virtual ~Abstract();

   public:
      static void printSettingsLocation();
      static QAction* addAction(QIcon icon, QString text, QString objectName, QObject* instance, auto slotFunction);

      static QString writeExampleResource(const QString& xmlResource);
      void populateMenuAndToolBar(const QString& xmlResource);

   protected:
      void setFunctions(ToolBarCreationFunction toolBarCreationFunction, MenuCreationFunction menuCreationFunction);

   private:
      void createToolBar(QDomElement thingElement);
      void createMenu(QDomElement thingElement, QMenu* parentMenu);

   private:
      QWidget* parentWidget;
      ToolBarCreationFunction toolBarCreationFunction;
      MenuCreationFunction menuCreationFunction;
   };
} // namespace Populated

#ifndef PopulatedAbstractHPP
#include "PopulatedAbstract.hpp"
#endif // NOT PopulatedAbstractHPP

#endif // NOT PopulatedAbstractH
