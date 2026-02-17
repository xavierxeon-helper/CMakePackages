#include "RainbowRectangle.h"

#include <QPainter>
#include <QTimer>

RainbowRectangle::RainbowRectangle(QQuickItem* parent)
   : QQuickPaintedItem(parent)
   , shade(300)
   , stretch(0.0)
   , orientation(Qt::Vertical)
   , inverse(false)
   , rainbow(300, shade)
{
   auto updateWrapper = [this]()
   {
      this->update();
   };

   QTimer* updateTimer = new QTimer(this);
   connect(updateTimer, &QTimer::timeout, updateWrapper); // update has default arguments
   updateTimer->start(100);
}

int RainbowRectangle::getShade() const
{
   return shade;
}

void RainbowRectangle::setShade(const int& value)
{
   shade = value;
   rainbow.changeShade(shade);
}

double RainbowRectangle::getStretch() const
{
   return stretch;
}

void RainbowRectangle::setStretch(const double& value)
{
   stretch = value;
}

Qt::Orientation RainbowRectangle::getOrientation() const
{
   return orientation;
}

void RainbowRectangle::setOrientation(const Qt::Orientation& value)
{
   orientation = value;
}

bool RainbowRectangle::getInverse() const
{
   return inverse;
}

void RainbowRectangle::setInverse(const bool& value)
{
   inverse = value;
}

void RainbowRectangle::paint(QPainter* painter)
{
   const QColor bgColor = rainbow.advanceColor();
   if (0.0 == stretch)
   {
      painter->fillRect(contentsBoundingRect(), bgColor);
   }
   else
   {
      const int width = boundingRect().width();
      const int height = boundingRect().height();
      if (Qt::Horizontal == orientation)
      {
         const double repeats = (double)width / (stretch * rainbow.getMaxIndex());

         for (int x = 0; x < width; x++)
         {
            const int offset = inverse ? (width - x) * repeats : x * repeats;
            const QColor color = rainbow.getColor(offset);
            painter->fillRect(QRect(x, 0, x, height), color);
         }
      }
      else
      {
         const double repeats = (double)height / (stretch * rainbow.getMaxIndex());

         for (int y = 0; y < height; y++)
         {
            const int offset = inverse ? (height - y) * repeats : y * repeats;
            const QColor color = rainbow.getColor(offset);
            painter->fillRect(QRect(0, y, width, y), color);
         }
      }
   }
}
