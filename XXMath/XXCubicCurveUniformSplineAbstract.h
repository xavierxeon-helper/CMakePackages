#ifndef XXCubicCurveUniformSplineAbstractH
#define XXCubicCurveUniformSplineAbstractH

#include <XXLinalgVector3.h>
#include <QJsonObject>

namespace XX
{
   namespace CubicCurve
   {
      class UniformSplineAbstract
      {
      public:
         UniformSplineAbstract();
         UniformSplineAbstract(const Linalg::Vector3& p0);

      public:
         QJsonObject save() const;
         void load(const QJsonObject& data);

         Linalg::Vector3 value(double parameter, uchar derivativeOrder = 0) const;
         int numberOfCurves() const;
         int numberOfPoints() const;

         double findParamter(const double& target, Linalg::Vector3::Index vectorIndex, double tolerance = 1e-9) const;
         Linalg::Vector3 findValue(const double& target, Linalg::Vector3::Index vectorIndex, uchar derivativeOrder = 0, double tolerance = 1e-9) const;

      protected:
         virtual void setStartPoint(const Linalg::Vector3& p);
         virtual void addCurvePoints(const Linalg::Vector3 p[3]);

         virtual Linalg::Vector3 calculate(double localParameter, int derivativeOrder, const Linalg::Vector3& p0, const Linalg::Vector3& p1, const Linalg::Vector3& p2, const Linalg::Vector3& p3) const = 0;

      protected:
         QList<Linalg::Vector3> points;

      private:
         friend XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const UniformSplineAbstract& spline);
      };

      /*!
         @addtogroup Streaming
         @{
         @ingroup XXMath
      */

      XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const UniformSplineAbstract& spline);

      //! @}
   } // namespace CubicCurve
} // namespace XX

#endif // NOT XXCubicCurveUniformSplineAbstractH
