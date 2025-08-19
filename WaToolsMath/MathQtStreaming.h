#ifndef MathQtStreamingH
#define MathQtStreamingH

#include "WaToolsMathExportDef.h"

#include <QDebug>
#include <QTextStream>

#include "MathVector3.h"

WATOOLSMATH_DECLSPEC QDebug operator<<(QDebug stream, const Math::Vector3& data);
WATOOLSMATH_DECLSPEC QDebug operator<<(QDebug stream, const Math::Spherical& data);

WATOOLSMATH_DECLSPEC QTextStream& operator<<(QTextStream& stream, const Math::Vector3& data);
WATOOLSMATH_DECLSPEC QTextStream& operator>>(QTextStream& stream, Math::Vector3& data);

#endif // NOT MathQtStreamingH
