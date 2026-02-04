#ifndef InterfaceQToolBarH
#define InterfaceQToolBarH

#include "InterfaceAbstract.h"

QT_BEGIN_NAMESPACE

class InterfaceQToolBar : public InterfaceAbstract
{
   Q_OBJECT

public:
   explicit InterfaceQToolBar(QObject* parent = nullptr);

public:
   QString domXml() const override;
   QString includeFile() const override;
   QString name() const override;
   QWidget* createWidget(QWidget* parent) override;
};

QT_END_NAMESPACE

#endif // NOT InterfaceQToolBarH
