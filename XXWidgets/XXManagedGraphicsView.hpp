#ifndef ManagedGraphicsViewHPP
#define ManagedGraphicsViewHPP

#include "XXManagedGraphicsView.h"

template <typename TargetClass>
void Managed::GraphicsView::onClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QPointF &, QGraphicsItem *))
{
   mousePressFunction = std::bind(memberFunction, instance, std::placeholders::_1, std::placeholders::_2);
}

#endif // NOT ManagedGraphicsViewHPP
