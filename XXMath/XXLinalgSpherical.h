#ifndef XXLinalgSphericalH
#define XXLinalgSphericalH

#include "XXMathExportDef.h"

#include <iostream>

#include <QDebug>
#include <QTextStream>

namespace XX
{
   namespace Linalg
   {
      //! @brief Spherical coordinates, used to represent points in 3D space.
      //! @ingroup XXMath

      class XXMATH_DECLSPEC Spherical
      {
      public:
         Spherical(const double& az = 0.0, const double& el = 0.0, const double& radius = 1.0);

      public:
         bool operator<(const Spherical& other) const;
         friend std::ostream& operator<<(std::ostream& out, const Spherical& value);

      public:
         double az = 0.0;
         double el = 0.0;
         double radius = 0.0;
      };

      /*!
         @addtogroup Streaming
         @{
         @ingroup XXMath
         @brief streaming operators for math types
      */
      std::ostream& operator<<(std::ostream& out, const Spherical& value);
      XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Spherical& data);

      //! @}

   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgSphericalH
