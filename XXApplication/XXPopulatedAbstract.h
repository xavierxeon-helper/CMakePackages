#ifndef XXPopulatedAbstractH
#define XXPopulatedAbstractH

#include "XXApplicationExportDef.h"

#include <QDomElement>
#include <QToolBar>
#include <QWidget>

namespace Populated
{
   class XXAPPLICATION_DECLSPEC Abstract
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
      static QAction* addFunctorAction(QIcon icon, QString text, QString objectName, QObject* parent, auto functor);
      static void setActionIcon(QObject* parent, QString objectName, QIcon icon);
      static void setActionShortcut(QObject* parent, QString objectName, QKeySequence shortcut);

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

#ifndef XXPopulatedAbstractHPP
#include "XXPopulatedAbstract.hpp"
#endif // NOT XXPopulatedAbstractHPP

#endif // NOT XXPopulatedAbstractH
