#include "DesignerPlugin.h"

#include "InterfaceQMenuBar.h"

DesignerPlugin::DesignerPlugin(QObject* parent)
   : QObject(parent)
   , widgets()
{
   widgets.append(new InterfaceQMenuBar(this));
}

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const
{
   return widgets;
}
