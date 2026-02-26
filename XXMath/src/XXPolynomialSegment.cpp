#include "XXPolynomialSegment.h"

XX::Polynomial::Segment::Segment(size_t degree)
   : Polynomial(degree)
{
}

XX::Polynomial::Segment::Segment(QVector<double> coefficents)
   : Polynomial(coefficents)
{
}
