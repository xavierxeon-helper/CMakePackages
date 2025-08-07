#ifndef ManagedGraphicsViewH
#define ManagedGraphicsViewH

#include <QGraphicsView>

namespace Managed
{
   class GraphicsView : public QGraphicsView
   {
      Q_OBJECT

   public:
      GraphicsView(QWidget* parent);

   public:
      template <typename TargetClass>
      void onClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QPointF&, QGraphicsItem*));

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
