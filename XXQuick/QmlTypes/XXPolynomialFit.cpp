#include "XXPolynomialFit.h"

XX::PolynomialFit::PolynomialFit(QQuickItem* parent)
   : QQuickItem(parent)
   , regression(nullptr)
{
}

XX::PolynomialFit::~PolynomialFit()
{
   if (regression)
      delete regression;
}

void XX::PolynomialFit::setValue(const size_t index, const double& value)
{
   if (!regression)
      return;

   regression->setValue(index, value);
}

void XX::PolynomialFit::clear()
{
   if (!regression)
      return;

   regression->clear();
}

void XX::PolynomialFit::fit(size_t degree, double threshold, size_t overFit, size_t maxSegmentLength) const
{
   if (!regression)
      return;

   regression->fit(degree, threshold, overFit, maxSegmentLength);
}

size_t XX::PolynomialFit::getSize() const
{
   return regression ? regression->size() : 0;
}

void XX::PolynomialFit::setSize(const size_t& value)
{
   if (regression)
      delete regression;

   regression = new XX::Polynomial::Regression(value);
}
