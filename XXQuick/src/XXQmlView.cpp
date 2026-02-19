#include "XXQmlView.h"

#include <QQmlContext>
#include <QQuickItem>

XX::QmlView::QmlView(QWindow* parent)
   : QQuickView(parent)
{
   setResizeMode(SizeRootObjectToView);
}

void XX::QmlView::setQuickProperty(const QString& name, QObject* object)
{
   rootContext()->setContextProperty(name, object);
}

void XX::QmlView::setQuickProperty(const QString& name, const QVariant& value)
{
   rootContext()->setContextProperty(name, value);
}

void XX::QmlView::tabletEvent(QTabletEvent* tabletEvent)
{
   //tabletEvent->accept();

   //const double x = tabletEvent->position().x();
   //const double y = tabletEvent->position().y();

   std::function<void(QQuickItem*)> childCrawler = [&](QQuickItem* parent)
   {
      for (QQuickItem* childItem : parent->childItems())
      {
         if (wantsTabletEvents(childItem))
            QGuiApplication::sendEvent(childItem, tabletEvent);

         childCrawler(childItem);
      }
   };

   childCrawler(contentItem());
}

bool XX::QmlView::wantsTabletEvents(const QQuickItem* item)
{
   static QMap<const QMetaObject*, bool> cache;

   const QMetaObject* mo = item->metaObject();
   if (cache.contains(mo))
      return cache[mo];

   const int index = mo->indexOfClassInfo("XXCaptureTablet");
   if (index < 0)
      return false;

   const QString text = mo->classInfo(index).value();
   bool wants = (text.toLower() == "true");

   cache.insert(mo, wants);
   return wants;
}
