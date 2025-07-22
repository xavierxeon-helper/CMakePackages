#ifndef ManagedTreeViewHPP
#define ManagedTreeViewHPP

#include <ManagedTreeView.h>

template <typename TargetClass>
void Managed::TreeView::onSelected(TargetClass* instance, void (TargetClass::*memberFunction)(QStandardItem*))
{
   selectedFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void Managed::TreeView::onDoubleClicked(TargetClass* instance, void (TargetClass::*memberFunction)(QStandardItem*))
{
   doubleClickFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void Managed::TreeView::onContextMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(QStandardItem*))
{
   contextMenuFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

#endif // NOT ManagedTreeViewHPP
