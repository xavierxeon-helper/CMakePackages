#ifndef XXMathQtStreamingH
#define XXMathQtStreamingH

#include "XXMathExportDef.h"

#include <QDebug>
#include <QTextStream>

#include "XXMathVector3.h"

/*!
   @addtogroup Streaming
   @{
   @ingroup XXMath
*/

XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const XX::Math::Vector3& data);
XXMATH_DECLSPEC QDebug operator<<(QDebug stream, const XX::Math::Spherical& data);

XXMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const XX::Math::Vector3& data);
XXMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, XX::Math::Vector3& data);

//! @}

#endif // NOT XXMathQtStreamingH
