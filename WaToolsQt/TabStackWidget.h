#ifndef TabStackWidgetH
#define TabStackWidgetH

#include <QWidget>

#include <QStackedWidget>
#include <QTabBar>
#include <QToolButton>

namespace TabStack
{
   class Widget : public QWidget
   {
      Q_OBJECT

   public:
      Widget(QWidget* parent);

   public:
      void addTab(QWidget* widget, const QString& label, int depth = 0);
      void setCornerWidget(QWidget* widget);

      QStringList getAllTabLabels() const;

      int depthCount() const;
      void setActiveDepth(int depth);
      QStringList getTabOrder(int depth) const;
      void setTabOrder(int depth, const QStringList& labels);

   private:
      struct TabInfo
      {
         QWidget* widget = nullptr;
         const QString label;

         using List = QList<TabInfo*>;
      };

      struct TabBarInfo
      {
         TabInfo::List tabOrder;
         QWidget* activeWidget = nullptr;
      };
      using DepthOrder = QList<TabBarInfo>;

   private:
      void tabSelected(int index);

   private:
      QTabBar* tabBar;
      QStackedWidget* stack;
      TabInfo::List infoList;
      DepthOrder depthOrder;
      int depthIndex;
   };
} // namespace TabStack

#endif // NOT TabStackWidgetH
