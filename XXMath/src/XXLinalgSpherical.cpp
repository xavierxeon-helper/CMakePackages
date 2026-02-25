#include "XXLinalgSpherical.h"

XX::Linalg::Spherical::Spherical(const double& az, const double& el, const double& radius)
   : az(az)
   , el(el)
   , radius(radius)
{
}

bool XX::Linalg::Spherical::operator<(const Spherical& other) const
{
   if (az < other.az)
      return true;
   else if (az > other.az)
      return false;
   else
      return (el < other.el);
}

//

std::ostream& XX::Linalg::operator<<(std::ostream& out, const Linalg::Spherical& value)
{
   out << "sperical[" << value.az << ", " << value.el << ", " << value.radius << "]";
   return out;
}

QDebug XX::Linalg::operator<<(QDebug stream, const Spherical& data)
{
   stream << "spherical[" << data.az << ", " << data.el << ", " << data.radius << "]";
   return stream;
}
