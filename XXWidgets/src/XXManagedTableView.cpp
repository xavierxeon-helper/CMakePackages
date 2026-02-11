#include "XXManagedTableView.h"

#include <QMenu>
#include <QMouseEvent>
#include <QSortFilterProxyModel>

XX::Managed::TableView::TableView(QWidget* parent)
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

void XX::Managed::TableView::setModel(QAbstractItemModel* model)
{
   QTableView::setModel(model);

   if (selectConnetion)
      disconnect(selectConnetion);

   selectConnetion = connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &TableView::selected);
}

QModelIndex XX::Managed::TableView::currentSourceIndex() const
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

void XX::Managed::TableView::selected(const QModelIndex& index)
{
   if (!selectedFunction)
      return;

   selectedFunction(index);
}

void XX::Managed::TableView::mouseDoubleClickEvent(QMouseEvent* event)
{
   if (!doubleClickFunction)
      return QTableView::mouseDoubleClickEvent(event);

   QModelIndex index = indexAt(event->pos());

   if (!doubleClickFunction(index))
      QTableView::mouseDoubleClickEvent(event);
}

void XX::Managed::TableView::contextMenuRequested(const QPoint& point)
{
   if (!contextMenuFunction)
      return;

   QModelIndex index = indexAt(point);
   QMenu* menu = contextMenuFunction(index);
   if (!menu)
      return;

   menu->exec(mapToGlobal(point));
}
