#ifndef InterfaceQMenuBarH
#define InterfaceQMenuBarH

#include "InterfaceAbstract.h"

class InterfaceQMenuBar : public InterfaceAbstract
{
   Q_OBJECT

public:
   explicit InterfaceQMenuBar(QObject* parent = nullptr);

public:
   QString domXml() const override;
   QString includeFile() const override;
   QString name() const override;
   QWidget* createWidget(QWidget* parent) override;
};

#endif // NOT InterfaceQMenuBarH
