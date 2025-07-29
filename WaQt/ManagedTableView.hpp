#ifndef ManagedTableViewHPP
#define ManagedTableViewHPP

#include "ManagedTableView.h"

template <typename TargetClass>
void Managed::TableView::onSelected(TargetClass* instance, void (TargetClass::*memberFunction)(const QModelIndex &))
{
   selectedFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void Managed::TableView::onDoubleClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QModelIndex&))
{
   doubleClickFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void Managed::TableView::onContextMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(const QModelIndex&))
{
   contextMenuFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

#endif // NOT ManagedTableViewHPP
