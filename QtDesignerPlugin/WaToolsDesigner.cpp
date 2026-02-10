#include "WaToolsQtDesigner.h"

#include "Gui/AnalogClock.h"
#include "Gui/PopulatedMenuBar.h"
#include "Gui/PopulatedToolBar.h"
#include "Interface/InterfaceNamedAbstract.h"

WaToolsQtDesigner::WaToolsQtDesigner(QObject* parent)
   : QObject(parent)
   , widgets()
{
   widgets.append(new Interface::NamedAbstract<AnalogClock>(this));
   widgets.append(new Interface::NamedAbstract<Populated::MenuBar>(this));
   widgets.append(new Interface::NamedAbstract<Populated::ToolBar>(this));
}

QList<QDesignerCustomWidgetInterface*> WaToolsQtDesigner::customWidgets() const
{
   return widgets;
}
