#include "XXPolynomial.h"

XX::Polynomial::Polynomial(size_t degree)
   : coefficents(degree + 1, 0.0)
{
}

XX::Polynomial::Polynomial(QVector<double> coefficents)
   : coefficents(coefficents)
{
}

XX::Polynomial::Polynomial(const Polynomial& other)
   : coefficents(other.coefficents)
{
}

XX::Polynomial& XX::Polynomial::operator=(const Polynomial& other)
{
   coefficents = other.coefficents;
   return *this;
}

double XX::Polynomial::operator()(const double& x) const
{
   return value(x);
}

bool XX::Polynomial::operator==(const Polynomial& other) const
{
   return (coefficents == other.coefficents);
}

bool XX::Polynomial::operator!=(const Polynomial& other) const
{
   return !(*this == other);
}

XX::Polynomial XX::Polynomial::operator+(const Polynomial& other) const
{
   const size_t maxSize = std::max(coefficents.size(), other.coefficents.size());
   XX::Polynomial result(maxSize);

   for (size_t index = 0; index < maxSize; index++)
   {
      const double myValue = (index < coefficents.size()) ? coefficents.at(index) : 0.0;
      const double otherValue = (index < other.coefficents.size()) ? other.coefficents.at(index) : 0.0;

      result.setCoefficient(index, myValue + otherValue);
   }

   return result;
}

XX::Polynomial XX::Polynomial::operator-(const Polynomial& other) const
{
   const size_t maxSize = std::max(coefficents.size(), other.coefficents.size());
   XX::Polynomial result(maxSize);

   for (size_t index = 0; index < maxSize; index++)
   {
      const double myValue = (index < coefficents.size()) ? coefficents.at(index) : 0.0;
      const double otherValue = (index < other.coefficents.size()) ? other.coefficents.at(index) : 0.0;

      result.setCoefficient(index, myValue - otherValue);
   }

   return result;
}

XX::Polynomial& XX::Polynomial::operator+=(const Polynomial& other)
{
   for (size_t index = 0; index < coefficents.size(); index++)
   {
      const double otherValue = (index < other.coefficents.size()) ? other.coefficents.at(index) : 0.0;
      coefficents[index] += otherValue;
   }

   return *this;
}

XX::Polynomial& XX::Polynomial::operator-=(const Polynomial& other)
{
   for (size_t index = 0; index < coefficents.size(); index++)
   {
      const double otherValue = (index < other.coefficents.size()) ? other.coefficents.at(index) : 0.0;
      coefficents[index] -= otherValue;
   }

   return *this;
}

double XX::Polynomial::value(const double& x) const
{
   double result = 0.0;

   for (size_t index = 0; index < coefficents.size(); index++)
   {
      const size_t expo = coefficents.size() - (index + 1);
      result += coefficents.at(index) * std::pow(x, expo);
   }
   return result;
}

void XX::Polynomial::setDegree(size_t degree)
{
   coefficents = QVector<double>(degree, 0.0);
}

size_t XX::Polynomial::getDegree() const
{
   return coefficents.size();
}

const QVector<double>& XX::Polynomial::getCoeficents() const
{
   return coefficents;
}

void XX::Polynomial::setCoefficient(size_t index, const double& value)
{
   if (index >= coefficents.size())
      return;

   coefficents[index] = value;
}

//

QDebug XX::operator<<(QDebug stream, const Polynomial& polynomial)
{
   stream << "Polynomial: y =";
   for (size_t index = 0; index < polynomial.coefficents.size(); index++)
   {
      if (0 != index)
         stream << qPrintable("+");

      int pow = polynomial.coefficents.size() - (index + 1);
      stream << polynomial.coefficents.at(index) << qPrintable("*x^" + QString::number(pow));
   }

   return stream;
}
