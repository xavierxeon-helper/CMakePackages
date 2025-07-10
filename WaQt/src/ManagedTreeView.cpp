
#include <ManagedTreeView.h>

#include <QMenu>
#include <QMouseEvent>
#include <QStandardItemModel>

Managed::TreeView::TreeView(QWidget* parent)
   : QTreeView(parent)
   , doubleClickFunction()
   , contextMenuFunction()
{
   setContextMenuPolicy(Qt::CustomContextMenu);
   connect(this, &QTreeView::customContextMenuRequested, this, &TreeView::customContextMenuRequested);
}

void Managed::TreeView::mouseDoubleClickEvent(QMouseEvent* event)
{
   if (!doubleClickFunction)
      return;

   QStandardItem* item = getItemAtPoint(event->pos());
   doubleClickFunction(item);
}

void Managed::TreeView::customContextMenuRequested(const QPoint& point)
{
   if (!contextMenuFunction)
      return;

   QStandardItem* item = getItemAtPoint(point);
   QMenu* menu = contextMenuFunction(item);
   if (!menu)
      return;

   menu->exec(mapToGlobal(point));
}

QStandardItem* Managed::TreeView::getItemAtPoint(const QPoint& point) const
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
