#ifndef XXLinalgGeneralH
#define XXLinalgGeneralH

#include <cmath>
#include <complex>

namespace XX
{
   namespace Linalg
   {

      // for 3d version see Linalg::Vector3
      template <typename RealType = float>
      std::complex<RealType> cartesianToPolar(const std::complex<RealType>& cartesian);

      template <typename RealType = float>
      std::complex<RealType> polarToCartesian(const std::complex<RealType>& polar);

   } // namespace Linalg
} // namespace XX

#ifndef XXLinalgGeneralHPP
#include "XXLinalg.hpp"
#endif // NOT XXLinalgGeneralHPP

#endif // NOT XXLinalgGeneralH
