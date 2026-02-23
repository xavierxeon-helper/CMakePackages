#ifndef RainbowRectangleH
#define RainbowRectangleH

#include <QQuickPaintedItem>

#include <XXRainbow.h>

namespace XX
{
   //! @brief a rainbow colored rectangle
   //! @ingroup XXQuick

   class RainbowRectangle : public QQuickPaintedItem
   {
      Q_OBJECT
      QML_NAMED_ELEMENT(RainbowRectangle)

      Q_PROPERTY(int shade READ getShade WRITE setShade)
      Q_PROPERTY(double stretch READ getStretch WRITE setStretch)
      Q_PROPERTY(Qt::Orientation orientation READ getOrientation WRITE setOrientation)
      Q_PROPERTY(bool inverse READ getInverse WRITE setInverse)

   public:
      RainbowRectangle(QQuickItem* parent = nullptr);

   private:
      int getShade() const;
      void setShade(const int& value);

      double getStretch() const;
      void setStretch(const double& value);

      Qt::Orientation getOrientation() const;
      void setOrientation(const Qt::Orientation& value);

      bool getInverse() const;
      void setInverse(const bool& value);

      void paint(QPainter* painter) override;

   private:
      int shade;
      double stretch;
      Qt::Orientation orientation;
      bool inverse;
      XX::Rainbow rainbow;
   };
} // namespace XX

#endif // NOT RainbowRectangleH
