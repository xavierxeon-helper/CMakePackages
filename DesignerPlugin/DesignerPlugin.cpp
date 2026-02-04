#include "DesignerPlugin.h"

#include "InterfaceQMenuBar.h"
#include "InterfaceQToolBar.h"

DesignerPlugin::DesignerPlugin(QObject* parent)
   : QObject(parent)
   , widgets()
{
   //widgets.append(new InterfaceQMenuBar(this));
   widgets.append(new InterfaceQToolBar(this));
}

QList<QDesignerCustomWidgetInterface*> DesignerPlugin::customWidgets() const
{
   return widgets;
}
