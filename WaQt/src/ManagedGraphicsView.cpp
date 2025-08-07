#include "ManagedGraphicsView.h"
#include <QMouseEvent>

Managed::GraphicsView::GraphicsView(QWidget* parent)
   : QGraphicsView(parent)
   , mousePressFunction()
{
}

void Managed::GraphicsView::mousePressEvent(QMouseEvent* event)
{
   if (!mousePressFunction)
      return QGraphicsView::mousePressEvent(event);

   QPointF point = mapToScene(event->pos());
   QGraphicsItem* item = itemAt(event->pos());

   if (!mousePressFunction(point, item))
      return QGraphicsView::mousePressEvent(event);
}
