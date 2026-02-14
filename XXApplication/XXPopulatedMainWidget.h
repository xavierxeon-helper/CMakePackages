#ifndef XXPopulatedMainWidgetH
#define XXPopulatedMainWidgetH

#include "XXApplicationExportDef.h"
#include "XXPopulatedAbstract.h"
#include "XXSingleton.h"
#include <QWidget>

#include <QMenuBar>

namespace XX
{
   namespace Populated
   {
      //! @brief main widget that can be populated with menu and tool bars based on XML resources
      //! @ingroup XXApplication

      class XXAPPLICATION_DECLSPEC MainWidget : public QWidget, public Abstract, public Singleton<MainWidget>
      {
         Q_OBJECT

      public:
         MainWidget();

      protected:
         void loadSettings();
         virtual void closeEvent(QCloseEvent* ce) override;
         virtual void placeMenuBar(QMenuBar* menuBar);

      private:
         QToolBar* findOrCreateToolBar(const QString& objectName);
         QMenu* findOrCreateMenu(const QString& objectName, const QString& text, QMenu* parentMenu);

      private:
         QMenuBar* menuBar;
      };
   } // namespace Populated
} // namespace XX

#endif // NOT XXPopulatedMainWidgetH
