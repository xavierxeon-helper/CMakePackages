#include "XXMathQtStreaming.h"

QDebug operator<<(QDebug stream, const Math::Vector3& data)
{
   stream << "[" << data[0] << ", " << data[1] << ", " << data[2] << "]";
   return stream;
}

QDebug operator<<(QDebug stream, const Math::Spherical& data)
{
   stream << "spherical[" << data.az << ", " << data.el << ", " << data.radius << "]";
   return stream;
}

QTextStream& operator<<(QTextStream& stream, const Math::Vector3& data)
{
   stream << "[" << data[0] << "," << data[1] << "," << data[2] << "]";
   return stream;
}

QTextStream& operator>>(QTextStream& stream, Math::Vector3& data)
{
   char dummy;
   stream >> dummy >> data[0] >> dummy >> data[1] >> dummy >> data[2] >> dummy;
   return stream;
}
