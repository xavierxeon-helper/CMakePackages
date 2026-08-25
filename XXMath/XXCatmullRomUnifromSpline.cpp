#include "XXCatmullRomUnifromSpline.h"

XX::CatmullRom::UnifromSpline::UnifromSpline(const Linalg::Vector3& startKnot)
   : CubicCurve::UniformSpline<CurveCalculator>(startKnot)
{
}

