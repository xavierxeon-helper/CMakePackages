#ifndef ManagedTreeViewHPP
#define ManagedTreeViewHPP

#include <ManagedTreeView.h>

#include <QMenu>
#include <QMouseEvent>
#include <QStandardItemModel>

inline Managed::TreeView::TreeView(QWidget* parent)
   : QTreeView(parent)
   , doubleClickFunction()
   , contextMenuFunction()
{
   setContextMenuPolicy(Qt::CustomContextMenu);
   connect(this, &QTreeView::customContextMenuRequested, this, &TreeView::customContextMenuRequested);
}

template <typename TargetClass>
void Managed::TreeView::onDoubleClicked(TargetClass* instance, void (TargetClass::*memberFunction)(QStandardItem*))
{
   doubleClickFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

template <typename TargetClass>
void Managed::TreeView::onConexteMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(QStandardItem*))
{
   contextMenuFunction = std::bind(memberFunction, instance, std::placeholders::_1);
}

inline void Managed::TreeView::mouseDoubleClickEvent(QMouseEvent* event)
{
   if (!doubleClickFunction)
      return;

   QStandardItem* item = getItemAtPoint(event->pos());
   doubleClickFunction(item);
}

inline void Managed::TreeView::customContextMenuRequested(const QPoint& point)
{
   if (!contextMenuFunction)
      return;

   QStandardItem* item = getItemAtPoint(point);
   QMenu* menu = contextMenuFunction(item);
   if (!menu)
      return;

   menu->exec(mapToGlobal(point));
}

inline QStandardItem* Managed::TreeView::getItemAtPoint(const QPoint& point) const
{
   QModelIndex index = indexAt(point);
   if (!index.isValid())
      return nullptr;

   QStandardItemModel* itemModel = qobject_cast<QStandardItemModel*>(model());
   if (!itemModel)
      return nullptr;

   QStandardItem* item = static_cast<QStandardItem*>(itemModel->itemFromIndex(index));
   return item;
}

#endif // NOT ManagedTreeViewHPP
