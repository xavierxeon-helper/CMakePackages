#ifndef ManagedTreeViewH
#define ManagedTreeViewH

#include <QTreeView>

#include <QStandardItem>

namespace Managed
{
   class TreeView : public QTreeView
   {
      Q_OBJECT

   public:
      TreeView(QWidget* parent);

   public:
      template <typename TargetClass>
      void onDoubleClicked(TargetClass* instance, void (TargetClass::*memberFunction)(QStandardItem*));

      template <typename TargetClass>
      void onConexteMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(QStandardItem*));

   private:
      using ItemFunction = std::function<void(QStandardItem*)>;
      using MenuFunction = std::function<QMenu*(QStandardItem*)>;

   private:
      void mouseDoubleClickEvent(QMouseEvent* event) override;
      void customContextMenuRequested(const QPoint& point);
      QStandardItem* getItemAtPoint(const QPoint& point) const;

   private:
      ItemFunction doubleClickFunction;
      MenuFunction contextMenuFunction;
   };
} // namespace Managed

#ifndef ManagedTreeViewHPP
#include "ManagedTreeView.hpp"
#endif // NOT ManagedTreeViewHPP

#endif // NOT ManagedTreeViewH
