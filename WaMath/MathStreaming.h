#ifndef MathStreamingH
#define MathStreamingH

#include <QDebug>
#include <QTextStream>

#include "MathVector3.h"

QDebug operator<<(QDebug stream, const Math::Vector3& data);
QDebug operator<<(QDebug stream, const Math::Spherical& data);

QTextStream& operator<<(QTextStream& stream, const Math::Vector3& data);
QTextStream& operator>>(QTextStream& stream, Math::Vector3& data);

#ifndef MathStreamingHPP
#include "MathStreaming.hpp"
#endif // NOT MathStreamingHPP

#endif // NOT MathStreamingH
