#include "ManagedTableView.h"

#include <QMenu>
#include <QMouseEvent>
#include <QSortFilterProxyModel>

Managed::TableView::TableView(QWidget* parent)
   : QTableView(parent)
   , selectConnetion()
   , selectedFunction()
   , doubleClickFunction()
   , contextMenuFunction()
{
   setSelectionBehavior(SelectRows);

   setContextMenuPolicy(Qt::CustomContextMenu);
   connect(this, &QTableView::customContextMenuRequested, this, &TableView::contextMenuRequested);
}

void Managed::TableView::setModel(QAbstractItemModel* model)
{
   QTableView::setModel(model);

   if (selectConnetion)
      disconnect(selectConnetion);

   selectConnetion = connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &TableView::selected);
}

QModelIndex Managed::TableView::currentSourceIndex() const
{
   if (model()->inherits("QSortFilterProxyModel"))
   {
      const QModelIndex filteredIndex = currentIndex();
      QSortFilterProxyModel* filterModel = qobject_cast<QSortFilterProxyModel*>(model());
      const QModelIndex sourceIndex = filterModel->mapToSource(filteredIndex);
      return sourceIndex;
   }

   return currentIndex();
}

void Managed::TableView::selected(const QModelIndex& index)
{
   if (!selectedFunction)
      return;

   selectedFunction(index);
}

void Managed::TableView::mouseDoubleClickEvent(QMouseEvent* event)
{
   if (!doubleClickFunction)
      return QTableView::mouseDoubleClickEvent(event);

   QModelIndex index = indexAt(event->pos());
   doubleClickFunction(index);
}

void Managed::TableView::contextMenuRequested(const QPoint& point)
{
   if (!contextMenuFunction)
      return;

   QModelIndex index = indexAt(point);
   QMenu* menu = contextMenuFunction(index);
   if (!menu)
      return;

   menu->exec(mapToGlobal(point));
}
