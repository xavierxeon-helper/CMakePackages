#ifndef XXMathQtStreamingH
#define XXMathQtStreamingH

#include "XXMathExportDef.h"

#include <QDebug>
#include <QTextStream>

#include "XXMathVector3.h"

namespace XX
{
   XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Math::Vector3& data);
   XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const Math::Spherical& data);

   XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Math::Vector3& data);
   XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Math::Vector3& data);
} // namespace XX

#endif // NOT XXMathQtStreamingH
