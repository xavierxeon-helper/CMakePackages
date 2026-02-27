#include "XXLinalgVector3.h"

#include "XXMath.h"

XX::Linalg::Vector3::Vector3(const double& x, const double& y, const double& z)
   : x(x)
   , y(y)
   , z(z)
{
}

bool XX::Linalg::Vector3::operator==(const Vector3& other) const
{
   if (x != other.x)
      return false;
   else if (y != other.y)
      return false;
   else if (z != other.z)
      return false;

   return true;
}

bool XX::Linalg::Vector3::operator<(const Vector3& other) const
{
   if (x < other.x)
      return true;
   else if (x > other.x)
      return false;
   else if (y < other.y)
      return true;
   else if (y > other.y)
      return false;
   else
      return (z < other.z);
}

XX::Linalg::Vector3 XX::Linalg::Vector3::operator+(const Vector3& other) const
{
   const double nx = x + other.x;
   const double ny = y + other.y;
   const double nz = z + other.z;

   return Vector3(nx, ny, nz);
}

XX::Linalg::Vector3& XX::Linalg::Vector3::operator+=(const Vector3& other)
{
   x += other.x;
   y += other.y;
   z += other.z;

   return *this;
}

const double& XX::Linalg::Vector3::operator[](const int index) const
{
   return data[index];
}

double& XX::Linalg::Vector3::operator[](const int index)
{
   return data[index];
}

const double& XX::Linalg::Vector3::getX() const
{
   return x;
}

const double& XX::Linalg::Vector3::getY() const
{
   return y;
}

const double& XX::Linalg::Vector3::getZ() const
{
   return z;
}

XX::Linalg::Vector3 XX::Linalg::Vector3::fromSpherical(const Spherical& spherical, const bool fromDegree)
{
   double az = spherical.az;
   double el = spherical.el;

   if (fromDegree)
   {
      az = Math::deg2Rad(az);
      el = Math::deg2Rad(el);
   }

   const double x = spherical.radius * std::sin(el) * std::cos(az);
   const double y = spherical.radius * std::sin(el) * std::sin(az);
   const double z = spherical.radius * std::cos(el);

   return Vector3(x, y, z);
}

XX::Linalg::Spherical XX::Linalg::Vector3::toSpherical(const bool toDegree) const
{
   const double radius = length();
   if (0.0 == radius)
      return Spherical();

   double el = std::acos(z / radius);

   const double planeRadius = std::sqrt((x * x) + (y * y));
   double az = (planeRadius > 0) ? std::acos(x / planeRadius) : 0.0;
   if (y < 0)
      az = (2 * Math::pi) - az;

   if (toDegree)
   {
      az = Math::rad2Deg(az);
      el = Math::rad2Deg(el);
   }

   return Spherical(az, el, radius);
}

double XX::Linalg::Vector3::length() const
{
   const double selfDot = dot(*this);
   return std::sqrt(selfDot);
}

XX::Linalg::Vector3 XX::Linalg::Vector3::norm() const
{
   const double l = length();
   if (0.0 == l)
      return Vector3(0.0, 0.0, 0.0);

   const double nx = x / l;
   const double ny = y / l;
   const double nz = z / l;

   return Vector3(nx, ny, nz);
}

double XX::Linalg::Vector3::dot(const Vector3& other) const
{
   return (x * other.x) + (y * other.y) + (z * other.z);
}

double XX::Linalg::Vector3::dotAngle(const Vector3& other, const bool toDegree) const
{
   const double d = dot(other);
   const double l = length() * other.length();
   double angle = std::acos(d / l);

   if (toDegree)
      angle = Math::rad2Deg(angle);

   return angle;
}

XX::Linalg::Vector3 XX::Linalg::Vector3::cross(const Vector3& other) const
{
   const double x = (y * other.z) - (z * other.y);
   const double y = (z * other.x) - (x * other.z);
   const double z = (x * other.y) - (y * other.x);

   return Vector3(x, y, z);
}

double XX::Linalg::Vector3::crossAngle(const Vector3& other, const bool toDegree) const
{
   const double c = cross(other).length();
   const double l = length() * other.length();
   double angle = std::asin(c / l);

   if (toDegree)
      angle = Math::rad2Deg(angle);

   return angle;
}

//

std::ostream& XX::Linalg::operator<<(std::ostream& out, const Linalg::Vector3& vector)
{
   out << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]";
   return out;
}

QDebug XX::Linalg::operator<<(QDebug stream, const Vector3& vector)
{
   stream << "[" << vector[0] << ", " << vector[1] << ", " << vector[2] << "]";
   return stream;
}

QTextStream& XX::Linalg::operator<<(QTextStream& stream, const Vector3& vector)
{
   stream << "[" << vector[0] << "," << vector[1] << "," << vector[2] << "]";
   return stream;
}

QTextStream& XX::Linalg::operator>>(QTextStream& stream, Vector3& vector)
{
   char dummy;
   stream >> dummy >> vector[0] >> dummy >> vector[1] >> dummy >> vector[2] >> dummy;
   return stream;
}
