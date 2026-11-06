#ifndef XXDropLabelHPP
#define XXDropLabelHPP

#include "XXDropLabel.h"

template <typename TargetClass>
void XX::DropLabel::onDrop(TargetClass* instance, void (TargetClass::*memberFunction)(const QString&))
{
   dropFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

#endif // NOT XXDropLabelHPP
