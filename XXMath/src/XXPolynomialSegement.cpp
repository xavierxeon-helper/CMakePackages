#include "XXPolynomialSegement.h"

XX::Polynomial::Segement::Segement(size_t degree)
   : Polynomial(degree)
{
}

XX::Polynomial::Segement::Segement(QVector<double> coefficents)
   : Polynomial(coefficents)
{
}
