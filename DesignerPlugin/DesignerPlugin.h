#ifndef DesignerPluginH
#define DesignerPluginH

// see /Users/waspe/Devel/Qt/6.10.2/Src/qttools/src/designer

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

class DesignerPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
   Q_OBJECT

   Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
   Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
   explicit DesignerPlugin(QObject* parent = nullptr);

public:
   QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
   QList<QDesignerCustomWidgetInterface*> widgets;
};

#endif // NOT DesignerPluginH
