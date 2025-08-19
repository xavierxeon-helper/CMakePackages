#ifndef ManagedGraphicsViewH
#define ManagedGraphicsViewH

#include <QGraphicsView>

#include "WaToolsQtExportDef.h"

namespace Managed
{
   class WATOOLSQT_DECLSPEC GraphicsView : public QGraphicsView
   {
      Q_OBJECT

   public:
      GraphicsView(QWidget* parent);

   public:
      template <typename TargetClass>
      void onClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QPointF&, QGraphicsItem*));

      void deactivateFrame();

   private:
      using ClickFunction = std::function<bool(const QPointF&, QGraphicsItem*)>;

   private:
      void mousePressEvent(QMouseEvent* event) override;

   private:
      ClickFunction mousePressFunction;
   };
} // namespace Managed

#ifndef ManagedGraphicsViewHPP
#include "ManagedGraphicsView.hpp"
#endif // NOT ManagedGraphicsViewHPP

#endif // NOT ManagedGraphicsViewH
