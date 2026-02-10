#ifndef WaToolsQtDesignerH
#define WaToolsQtDesignerH

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

class WaToolsQtDesigner : public QObject, public QDesignerCustomWidgetCollectionInterface
{
   Q_OBJECT

   Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
   Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
   explicit WaToolsQtDesigner(QObject* parent = nullptr);

public:
   QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
   QList<QDesignerCustomWidgetInterface*> widgets;
};

#endif // NOT WaToolsQtDesignerH
