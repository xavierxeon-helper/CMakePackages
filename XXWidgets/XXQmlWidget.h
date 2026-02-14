#ifndef XXWorkFlowQmlWidgetH
#define XXWorkFlowQmlWidgetH

#include "XXWidgetsExportDef.h"
#include <QQuickWidget>

namespace XX
{
   //! @brief a wrapper for QQuickWidget
   //! @ingroup XXWidgets

   class XXWIDGETS_DECLSPEC QmlWidget : public QQuickWidget
   {
      Q_OBJECT

   public:
      QmlWidget(QWidget* parent);

   public:
      void setQuickProperty(const QString& name, QObject* object);
      void setQuickProperty(const QString& name, const QVariant& value);
   };
} // namespace XX

#endif // NOT XXWorkFlowQmlWidgetH
