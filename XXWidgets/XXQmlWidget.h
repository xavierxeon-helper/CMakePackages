#ifndef XXWorkFlowQmlWidgetH
#define XXWorkFlowQmlWidgetH

#include "XXWidgetsExportDef.h"
#include <QQmlPropertyMap>
#include <QQuickWidget>

namespace XX
{
   //! @brief a wrapper for QQuickWidget
   //! @ingroup XXWidgets

   class XXWIDGETS_DECLSPEC QmlWidget : public QQuickWidget
   {
      Q_OBJECT

   public:
      class PropertyMap;

   public:
      QmlWidget(QWidget* parent);

   public:
      void setQuickProperty(const QString& name, QObject* object);
      void setQuickProperty(const QString& name, const QVariant& value);
   };

   class XXWIDGETS_DECLSPEC QmlWidget::PropertyMap : public QQmlPropertyMap
   {
      Q_OBJECT

   public:
      PropertyMap(QmlWidget* widget, const QString& qmlName);
   };
} // namespace XX

#endif // NOT XXWorkFlowQmlWidgetH
