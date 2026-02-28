#include "XXPolynomialSegment.h"

XX::Polynomial::Segment::Segment(size_t degree)
   : Polynomial(degree)
   , start(0.0)
   , end(0.0)
{
}

XX::Polynomial::Segment::Segment(QVector<double> coefficents)
   : Polynomial(coefficents)
   , start(0.0)
   , end(0.0)
{
}

const double& XX::Polynomial::Segment::getStart() const
{
   return start;
}

const double& XX::Polynomial::Segment::getEnd() const
{
   return end;
}

double XX::Polynomial::Segment::getLength() const
{
   return (end - start);
}

void XX::Polynomial::Segment::setStart(const double& value)
{
   start = value;
}

void XX::Polynomial::Segment::setEnd(const double& value)
{
   end = value;
}

double XX::Polynomial::Segment::value(const double& x) const
{
   return Polynomial::value(x - start);
}

void XX::Polynomial::Segment::load(const QJsonObject& data)
{
}

QJsonObject XX::Polynomial::Segment::save() const
{
   QJsonObject base = Polynomial::save();
   base["start"] = start;
   base["end"] = end;

   return base;
}

//

QDebug XX::operator<<(QDebug stream, const Polynomial::Segment& segment)
{
   stream << "Segment[" << segment.start << segment.end << "] with";
   stream << static_cast<Polynomial>(segment);
   return stream;
}
