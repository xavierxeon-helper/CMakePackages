#ifndef RainbowRectangleH
#define RainbowRectangleH

#include <QQuickPaintedItem>

#include <QLinearGradient>

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
      Q_PROPERTY(double rotation READ getRotation WRITE setRotation)

   public:
      RainbowRectangle(QQuickItem* parent = nullptr);

   private:
      int getShade() const;
      void setShade(const int& value);

      double getStretch() const;
      void setStretch(const double& value);

      double getRotation() const;
      void setRotation(const double& value);

      void updateDirection();
      void updateColor();

      void paint(QPainter* painter) override;

   private:
      int shade;
      double stretch;
      double rotation;
      XX::Rainbow rainbow;
      QLinearGradient gradient;
   };
} // namespace XX

#endif // NOT RainbowRectangleH
