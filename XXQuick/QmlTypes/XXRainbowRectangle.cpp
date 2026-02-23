#include "XXRainbowRectangle.h"

#include <QPainter>
#include <QTimer>

XX::RainbowRectangle::RainbowRectangle(QQuickItem* parent)
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
}

Qt::Orientation XX::RainbowRectangle::getOrientation() const
{
   return orientation;
}

void XX::RainbowRectangle::setOrientation(const Qt::Orientation& value)
{
   orientation = value;
}

bool XX::RainbowRectangle::getInverse() const
{
   return inverse;
}

void XX::RainbowRectangle::setInverse(const bool& value)
{
   inverse = value;
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
      // create gradient
      QLinearGradient gradient;
      gradient.setStart(QPointF(0, 0));
      if (Qt::Horizontal == orientation)
         gradient.setFinalStop(QPointF(stretch * rainbow.getMaxIndex(), 0));
      else
         gradient.setFinalStop(QPointF(0, stretch * rainbow.getMaxIndex()));
      gradient.setSpread(QGradient::RepeatSpread);

      for (int index = 0; index < rainbow.getMaxIndex(); index++)
      {
         const int offset = inverse ? (rainbow.getMaxIndex() - index) : index;
         const QColor color = rainbow.getColor(offset);

         const double pos = (double)index / (double)rainbow.getMaxIndex();
         gradient.setColorAt(pos, color);
      }

      // draw
      const QBrush gradientBrush(gradient);
      painter->fillRect(contentsBoundingRect(), gradientBrush);
   }
}
