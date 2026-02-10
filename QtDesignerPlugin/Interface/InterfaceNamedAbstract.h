#ifndef InterfaceNamedAbstractH
#define InterfaceNamedAbstractH

#include "InterfaceAbstract.h"

namespace Interface
{
   template <typename WidgetClass>
   class NamedAbstract : public Abstract
   {
   public:
      explicit NamedAbstract(QObject* parent);

   public:
      virtual QString domXml() const override;
      virtual QString includeFile() const override;
      virtual QString name() const override;
      virtual QWidget* createWidget(QWidget* parent) override;

   private:
      QString widgetClassName;
      QString widgetFileName;
   };
} // namespace Interface

#ifndef InterfaceNamedAbstractHPP
#include "InterfaceNamedAbstract.hpp"
#endif // NOT InterfaceNamedAbstractHPP

#endif // NOT InterfaceNamedAbstractH
