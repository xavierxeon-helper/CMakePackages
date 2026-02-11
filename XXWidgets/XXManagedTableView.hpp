#ifndef XXManagedTableViewHPP
#define XXManagedTableViewHPP

#include "XXManagedTableView.h"

template <typename TargetClass>
void XX::Managed::TableView::onSelected(TargetClass* instance, void (TargetClass::*memberFunction)(const QModelIndex&))
{
   selectedFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void XX::Managed::TableView::onDoubleClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QModelIndex&))
{
   doubleClickFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void XX::Managed::TableView::onContextMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(const QModelIndex&))
{
   contextMenuFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

#endif // NOT XXManagedTableViewHPP
