#ifndef XXLocalTextBrowserH
#define XXLocalTextBrowserH

#include "XXWidgetsExportDef.h"
#include <QTextBrowser>

class XXWIDGETS_DECLSPEC LocalTextBrowser : public QTextBrowser
{
   Q_OBJECT

public:
   LocalTextBrowser(QWidget* parent);

private:
   QVariant loadResource(int type, const QUrl& name) override;
};

#endif // NOT XXLocalTextBrowserH
