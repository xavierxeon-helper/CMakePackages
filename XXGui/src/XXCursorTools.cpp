#include "XXCursorTools.h"

#include <QGuiApplication>
#include <QPainter>
#include <QSvgRenderer>

QCursor XX::CursorTools::createSvgCursor(const QString& resourcePath, const QSize& size, const QPoint& hotspot, const QColor& tint)
{
   QSvgRenderer renderer(resourcePath);

   QGuiApplication* app = qobject_cast<QGuiApplication*>(QGuiApplication::instance());

   const qreal dpr = app->devicePixelRatio();
   QPixmap pixmap(size * dpr);
   pixmap.setDevicePixelRatio(dpr);
   pixmap.fill(Qt::transparent);

   QPainter painter(&pixmap);
   renderer.render(&painter, QRectF(QPointF(0, 0), size));
   painter.end();

   if (tint.isValid())
   {
      QPainter tintPainter(&pixmap);
      tintPainter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
      tintPainter.fillRect(pixmap.rect(), tint);
      tintPainter.end();
   }

   return QCursor(pixmap, hotspot.x(), hotspot.y());
}