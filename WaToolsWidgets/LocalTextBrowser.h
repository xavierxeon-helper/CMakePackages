#ifndef LocalTextBrowserH
#define LocalTextBrowserH

#include "WaToolsWidgetsExportDef.h"
#include <QTextBrowser>

class WATOOLSWIDGETS_DECLSPEC LocalTextBrowser : public QTextBrowser
{
   Q_OBJECT

public:
   LocalTextBrowser(QWidget* parent);

private:
   QVariant loadResource(int type, const QUrl& name) override;
};

#endif // NOT LocalTextBrowserH
