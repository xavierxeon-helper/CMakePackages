#ifndef XXManagedGraphicsViewHPP
#define XXManagedGraphicsViewHPP

#include "XXManagedGraphicsView.h"

template <typename TargetClass>
void XX::Managed::GraphicsView::onClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QPointF&, QGraphicsItem*))
{
   mousePressFunction = std::bind(memberFunction, instance, std::placeholders::_1, std::placeholders::_2);
}

#endif // NOT XXManagedGraphicsViewHPP
