#include "XXColorSpace.h"

#include <QtMath>

QColor XX::ColorSpace::fromCIE(const XYB& xyb)
{
   const double z = 1.0 - xyb.x - xyb.y;
   const double Y = xyb.brightness;
   const double X = (Y / xyb.y) * xyb.x;
   const double Z = (Y / xyb.y) * z;

   double r = X * 1.656492 - Y * 0.354851 - Z * 0.255038;
   double g = -X * 0.707196 + Y * 1.655397 + Z * 0.036152;
   double b = X * 0.051713 - Y * 0.121364 + Z * 1.011530;

   auto gammaCorrection = [](const double& value)
   {
      if (value <= 0.0031308)
         return 12.92 * value;
      else
         return (1.055) * qPow(value, (1.0 / 2.4)) - 0.055;
   };

   r = gammaCorrection(r);
   g = gammaCorrection(g);
   b = gammaCorrection(b);

   auto roundAndClamp = [](double value)
   {
      if (value < 0.0)
         value = 0.0;
      else if (value > 1.0)
         value = 1.0;

      return qRound(value * 255);
   };

   const int red = roundAndClamp(r);
   const int green = roundAndClamp(g);
   const int blue = roundAndClamp(b);

   const QColor color(red, green, blue);
   return color;
}

XX::ColorSpace::XYB XX::ColorSpace::toCIE(const QColor& color)
{
   double red = color.red() / 255.0;
   double green = color.green() / 255.0;
   double blue = color.blue() / 255.0;

   auto gammaCorrection = [](const double& value)
   {
      if (value > 0.04045)
         return qPow((value + 0.055) / 1.055, 2.4);
      else
         return value / 12.92;
   };

   red = gammaCorrection(red);
   green = gammaCorrection(green);
   blue = gammaCorrection(blue);

   double X = red * 0.4124 + green * 0.3576 + blue * 0.1805;
   double Y = red * 0.2126 + green * 0.7152 + blue * 0.0722;
   double Z = red * 0.0193 + green * 0.1192 + blue * 0.9505;

   XYB xyb;
   xyb.x = X / (X + Y + Z);
   xyb.y = Y / (X + Y + Z);
   xyb.brightness = Y;

   return xyb;
}
