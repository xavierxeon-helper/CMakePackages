#include "XXRainbowRectangle.h"

#include <QPainter>
#include <QTimer>
#include <QtMath>

XX::RainbowRectangle::RainbowRectangle(QQuickItem* parent)
   : QQuickPaintedItem(parent)
   , shade(300)
   , stretch(0.0)
   , rotation(180.0)
   , rainbow(300, shade)
   , gradient()
{
   gradient.setStart(QPointF(0, 0));
   gradient.setSpread(QGradient::RepeatSpread);
   updateDirection();

   auto updateWrapper = [this]()
   {
      this->update();
   };

   QTimer* updateTimer = new QTimer(this);
   connect(updateTimer, &QTimer::timeout, updateWrapper); // update has default arguments
   updateTimer->start(100);
}

int XX::RainbowRectangle::getShade() const
{
   return shade;
}

void XX::RainbowRectangle::setShade(const int& value)
{
   shade = value;
   rainbow.changeShade(shade);
}

double XX::RainbowRectangle::getStretch() const
{
   return stretch;
}

void XX::RainbowRectangle::setStretch(const double& value)
{
   stretch = value;
   if (stretch < 0.0)
      stretch = 0.0;

   updateDirection();
}

double XX::RainbowRectangle::getRotation() const
{
   return rotation;
}

void XX::RainbowRectangle::setRotation(const double& value)
{
   rotation = value;
   while (rotation < 0)
      rotation += 360;
   while (rotation >= 360)
      rotation -= 360;

   updateDirection();
}

void XX::RainbowRectangle::updateDirection()
{
   const double radius = stretch * rainbow.getMaxIndex();
   const double angle = qDegreesToRadians(rotation - 90);

   const double x = radius * qSin(angle);
   const double y = radius * qCos(angle);
   gradient.setFinalStop(QPointF(x, y));
}

void XX::RainbowRectangle::updateColor()
{
   for (int index = 0; index < rainbow.getMaxIndex(); index++)
   {
      const QColor color = rainbow.getColor(index);

      const double pos = (double)index / (double)rainbow.getMaxIndex();
      gradient.setColorAt(pos, color);
   }
}

void XX::RainbowRectangle::paint(QPainter* painter)
{
   const QColor bgColor = rainbow.advanceColor();
   if (0.0 == stretch)
   {
      const QBrush solidBrush(bgColor);
      painter->fillRect(contentsBoundingRect(), solidBrush);
   }
   else
   {
      updateColor();
      const QBrush gradientBrush(gradient);
      painter->fillRect(contentsBoundingRect(), gradientBrush);
   }
}
