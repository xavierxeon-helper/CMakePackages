#include "ManagedTreeView.h"

#include <QMenu>
#include <QMouseEvent>
#include <QStandardItemModel>

Managed::TreeView::TreeView(QWidget* parent)
   : QTreeView(parent)
   , selectConnetion()
   , selectedFunction()
   , doubleClickFunction()
   , contextMenuFunction()
{
   setContextMenuPolicy(Qt::CustomContextMenu);
   connect(this, &QTreeView::customContextMenuRequested, this, &TreeView::contextMenuRequested);
}

void Managed::TreeView::setModel(QAbstractItemModel* model)
{
   QTreeView::setModel(model);

   if (selectConnetion)
      disconnect(selectConnetion);

   selectConnetion = connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &TreeView::selected);
}

void Managed::TreeView::selected(const QModelIndex& index)
{
   if (!index.isValid())
      return;

   QStandardItem* item = getItemFromIndex(index);
   if (selectedFunction)
      selectedFunction(item);
}

void Managed::TreeView::mouseDoubleClickEvent(QMouseEvent* event)
{
   if (!doubleClickFunction)
      return;

   QStandardItem* item = getItemAtPoint(event->pos());
   doubleClickFunction(item);
}

void Managed::TreeView::contextMenuRequested(const QPoint& point)
{
   if (!contextMenuFunction)
      return;

   QStandardItem* item = getItemAtPoint(point);
   QMenu* menu = contextMenuFunction(item);
   if (!menu)
      return;

   menu->exec(mapToGlobal(point));
}

QStandardItem* Managed::TreeView::getItemFromIndex(const QModelIndex& index) const
{
   if (!index.isValid())
      return nullptr;

   QStandardItemModel* itemModel = qobject_cast<QStandardItemModel*>(model());
   if (!itemModel)
      return nullptr;

   QStandardItem* item = static_cast<QStandardItem*>(itemModel->itemFromIndex(index));
   return item;
}

QStandardItem* Managed::TreeView::getItemAtPoint(const QPoint& point) const
{
   QModelIndex index = indexAt(point);
   return getItemFromIndex(index);
}
