#ifndef XXQmlViewH
#define XXQmlViewH

#include "XXGuiExportDef.h"
#include <QQuickView>

namespace XX
{
   //! @brief a wrapper for QQuickView
   //! @ingroup XXGui

   class XXGUI_DECLSPEC QmlView : public QQuickView
   {
      Q_OBJECT

   public:
      QmlView(QWindow* parent = nullptr);

   public:
      void setQuickProperty(const QString& name, QObject* object);
      void setQuickProperty(const QString& name, const QVariant& value);

   private:
      void tabletEvent(QTabletEvent* tabletEvent) override;
      bool wantsTabletEvents(const QQuickItem* item);
   };
} // namespace XX

#endif // NOT XXQmlViewH
