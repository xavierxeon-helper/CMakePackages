#ifndef XXLocalTextBrowserH
#define XXLocalTextBrowserH

#include "XXWidgetsExportDef.h"
#include <QTextBrowser>

namespace XX
{
   //! @brief a QTextBrowser that can load local resources
   /*! @details can load local resources (e.g. images) from the resource system
      the resource path is expected to be in the format ":/path/to/resource
   */
   //! @ingroup XXWidgets

   class XXWIDGETS_DECLSPEC LocalTextBrowser : public QTextBrowser
   {
      Q_OBJECT

   public:
      LocalTextBrowser(QWidget* parent);

   private:
      QVariant loadResource(int type, const QUrl& name) override;
   };

} // namespace XX

#endif // NOT XXLocalTextBrowserH
