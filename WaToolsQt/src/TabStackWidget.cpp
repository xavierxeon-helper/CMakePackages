#include "TabStackWidget.h"

#include <QGridLayout>
#include <QToolButton>

TabStack::Widget::Widget(QWidget* parent)
   : QWidget(parent)
   , tabBar(nullptr)
   , stack(nullptr)
   , infoList()
   , depthOrder()
   , depthIndex(0)
{
   tabBar = new QTabBar(this);
   tabBar->setDocumentMode(true);
   connect(tabBar, &QTabBar::tabBarClicked, this, &TabStack::Widget::tabSelected);

   stack = new QStackedWidget(this);

   QGridLayout* masterLayout = new QGridLayout(this);
   masterLayout->setContentsMargins(0, 0, 0, 0);
   masterLayout->setSpacing(0);

   masterLayout->addWidget(tabBar, 0, 0);
   masterLayout->addWidget(stack, 1, 0, 2, 1);

   while (depthOrder.size() < 3)
      depthOrder.append(TabBarInfo{});
}

void TabStack::Widget::addTab(QWidget* widget, const QString& label, int depth)
{
   stack->addWidget(widget);

   TabInfo* info = new TabInfo{widget, label};
   infoList.append(info);

   while (depthOrder.size() <= depth)
      depthOrder.append(TabBarInfo{});

   depthOrder[depth].tabOrder.append(info);
}

void TabStack::Widget::setCornerWidget(QWidget* widget)
{
   QGridLayout* masterLayout = qobject_cast<QGridLayout*>(layout());
   masterLayout->addWidget(widget, 0, 1, Qt::AlignRight);
}

QStringList TabStack::Widget::getAllTabLabels() const
{
   QStringList labels;

   for (TabInfo* info : std::as_const(infoList))
      labels.append(info->label);

   return labels;
}

int TabStack::Widget::depthCount() const
{
   return depthOrder.size();
}

void TabStack::Widget::setActiveDepth(int depth)
{
   depthIndex = depth;
   while (tabBar->count() > 0)
      tabBar->removeTab(0);

   int activeindex = -1;

   const TabBarInfo& barInfo = depthOrder[depthIndex];
   for (int index = 0; index < barInfo.tabOrder.size(); index++)
   {
      TabInfo* info = barInfo.tabOrder.at(index);
      tabBar->addTab(info->label);

      if (barInfo.activeWidget == info->widget)
         activeindex = index;
   }

   qDebug() << barInfo.tabOrder << barInfo.activeWidget << activeindex;

   if (-1 != activeindex && barInfo.activeWidget)
   {
      tabBar->setCurrentIndex(activeindex);
      stack->setCurrentWidget(barInfo.activeWidget);
   }
   else
   {
      tabBar->setCurrentIndex(0);
      tabSelected(0);
   }
}

QStringList TabStack::Widget::getTabOrder(int depth) const
{
   if (depth > depthOrder.size() || depth < 0)
      return QStringList();

   QStringList labels;

   const TabBarInfo& barInfo = depthOrder[depth];
   for (TabInfo* info : std::as_const(barInfo.tabOrder))
      labels.append(info->label);

   return labels;
}

void TabStack::Widget::setTabOrder(int depth, const QStringList& labels)
{
   if (depth < 0)
      return;

   if (depth >= depthOrder.size())
   {
      while (depthOrder.size() <= depth)
         depthOrder.append(TabBarInfo{});
   }

   auto findInfo = [&](const QString& label) -> TabInfo*
   {
      for (TabInfo* info : std::as_const(infoList))
      {
         if (info->label == label)
            return info;
      }
      return nullptr;
   };

   TabBarInfo& barInfo = depthOrder[depth];
   barInfo.tabOrder.clear();
   barInfo.activeWidget = nullptr;

   for (const QString& label : labels)
   {
      TabInfo* info = findInfo(label);
      if (!info)
         continue;

      barInfo.tabOrder.append(info);
   }
}

void TabStack::Widget::tabSelected(int index)
{
   TabBarInfo& barInfo = depthOrder[depthIndex];

   TabInfo* info = barInfo.tabOrder.at(index);
   stack->setCurrentWidget(info->widget);
   barInfo.activeWidget = info->widget;
}
