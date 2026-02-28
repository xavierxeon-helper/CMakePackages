#ifndef XXLinalgSphericalH
#define XXLinalgSphericalH

#include "XXMathExportDef.h"

#include <iostream>

#include <QDebug>

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

      public:
         double az = 0.0;
         double el = 0.0;
         double radius = 0.0;

      private:
         friend XXMATH_DECLSPEC std::ostream& operator<<(std::ostream& out, const Spherical& spherial);
         friend XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Spherical& spherial);
      };

      /*!
         @addtogroup Streaming
         @{
         @ingroup XXMath
      */

      XXMATH_DECLSPEC std::ostream& operator<<(std::ostream& out, const Spherical& spherial);
      XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Spherical& spherial);

      //! @}

   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgSphericalH
