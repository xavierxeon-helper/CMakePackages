#ifndef ManagedTableViewH
#define ManagedTableViewH

#include "WaToolsWidgetsExportDef.h"
#include <QTableView>

namespace Managed
{
   class WATOOLSWIDGETS_DECLSPEC TableView : public QTableView
   {
      Q_OBJECT
   public:
      TableView(QWidget* parent);

   public:
      template <typename TargetClass>
      void onSelected(TargetClass* instance, void (TargetClass::*memberFunction)(const QModelIndex&));

      template <typename TargetClass>
      void onDoubleClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QModelIndex&));

      template <typename TargetClass>
      void onContextMenu(TargetClass* instance, QMenu* (TargetClass::*memberFunction)(const QModelIndex&));

      void setModel(QAbstractItemModel* model) override;
      QModelIndex currentSourceIndex() const;

   private:
      void selected(const QModelIndex& index);
      void mouseDoubleClickEvent(QMouseEvent* event) override;
      void contextMenuRequested(const QPoint& point);

   private:
      using SelectFunction = std::function<void(const QModelIndex&)>;
      using DoubleClickFunction = std::function<bool(const QModelIndex&)>;
      using MenuFunction = std::function<QMenu*(const QModelIndex&)>;

   private:
      QMetaObject::Connection selectConnetion;
      SelectFunction selectedFunction;
      DoubleClickFunction doubleClickFunction;
      MenuFunction contextMenuFunction;
   };
} // namespace Managed

#ifndef ManagedTableViewHPP
#include "ManagedTableView.hpp"
#endif // NOT ManagedTableViewHPP

#endif // NOT ManagedTableViewH
