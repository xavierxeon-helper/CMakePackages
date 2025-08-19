#ifndef ManagedTreeViewH
#define ManagedTreeViewH

#include "WaToolsQtExportDef.h"
#include <QTreeView>

#include <QStandardItem>

namespace Managed
{
   class WATOOLSQT_DECLSPEC TreeView : public QTreeView
   {
      Q_OBJECT

   public:
      TreeView(QWidget* parent);

   public:
      template <typename TargetClass>
      void onSelected(TargetClass* instance, void (TargetClass::*memberFunction)(QStandardItem*));

      template <typename TargetClass>
      void onDoubleClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(QStandardItem*));

      template <typename TargetClass>
      void onContextMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(QStandardItem*));

      void setModel(QAbstractItemModel* model) override;
      QModelIndex currentSourceIndex() const;

   private:
      using SelectFunction = std::function<void(QStandardItem*)>;
      using DoubleClickFunction = std::function<bool(QStandardItem*)>;
      using MenuFunction = std::function<QMenu*(QStandardItem*)>;

   private:
      void selected(const QModelIndex& index);
      void mouseDoubleClickEvent(QMouseEvent* event) override;
      void contextMenuRequested(const QPoint& point);
      QStandardItem* getItemFromIndex(const QModelIndex& index) const;
      QStandardItem* getItemAtPoint(const QPoint& point) const;

   private:
      QMetaObject::Connection selectConnetion;
      SelectFunction selectedFunction;
      DoubleClickFunction doubleClickFunction;
      MenuFunction contextMenuFunction;
   };
} // namespace Managed

#ifndef ManagedTreeViewHPP
#include "ManagedTreeView.hpp"
#endif // NOT ManagedTreeViewHPP

#endif // NOT ManagedTreeViewH
