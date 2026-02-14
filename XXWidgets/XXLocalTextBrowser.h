#ifndef XXLocalTextBrowserH
#define XXLocalTextBrowserH

#include "XXWidgetsExportDef.h"
#include <QTextBrowser>

namespace XX
{
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
