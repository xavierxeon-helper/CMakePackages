#ifndef XXLinalgVector3H
#define XXLinalgVector3H

#include "XXMathExportDef.h"

#include <iostream>

#include <QDebug>
#include <QTextStream>

#include "XXLinalgSpherical.h"

namespace XX
{
   namespace Linalg
   {
      //! @brief 3D vector, used to represent points or directions in 3D space.
      //! @ingroup XXMath

      class XXMATH_DECLSPEC Vector3
      {
         enum Index
         {
            X = 0,
            Y = 1,
            Z = 2
         };

      public:
         Vector3(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0);

      public:
         bool operator==(const Vector3& other) const;
         bool operator<(const Vector3& other) const;

         Vector3 operator+(const Vector3& other) const;
         Vector3& operator+=(const Vector3& other);

         const double& operator[](const int index) const;
         double& operator[](const int index);

      public:
         const double& getX() const;
         const double& getY() const;
         const double& getZ() const;

         // for 2d version see MathGeneral.h
         static Vector3 fromSpherical(const Spherical& spherical, const bool fromDegree = true);
         Spherical toSpherical(const bool toDegree = true) const;

         double length() const;
         Vector3 norm() const;

         double dot(const Vector3& other) const;
         double dotAngle(const Vector3& other, const bool toDegree = true) const;

         Vector3 cross(const Vector3& other) const;
         double crossAngle(const Vector3& other, const bool toDegree = true) const;

      private:
         friend XXMATH_DECLSPEC std::ostream& operator<<(std::ostream& out, const Vector3& vector);
         friend XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Vector3& vector);
         friend XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Vector3& vector);
         friend XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Vector3& vector);

      private:
         union
         {
            struct
            {
               double x;
               double y;
               double z;
            };
            double data[3];
         };
      };

      /*!
         @addtogroup Streaming
         @{
         @ingroup XXMath
         @brief streaming operators for vector3
      */

      XXMATH_DECLSPEC std::ostream& operator<<(std::ostream& out, const Vector3& vector);
      XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Vector3& vector);
      XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Vector3& vector);
      XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Vector3& vector);

      //! @}

   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgVector3H
