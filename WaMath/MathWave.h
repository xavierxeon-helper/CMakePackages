#ifndef MathWaveH
#define MathWaveH

// see https://beltoforion.de/en/recreational_mathematics/2d-wave-equation.php

#include <list>
#include <thread>
#include <vector>

#include "../WaTools/DoubleBuffer.h"
#include "../WaTools/Matrix.h"
#include "MathVector3.h"

namespace Math
{
   class Wave
   {
   public:
      Wave(const Size& size, const int& threadCount = 4);

   public:
      void step(const double& time);
      const Matrix<double>& getHeightField() const;

      const Size& getSize() const;

      const double& getFrequency() const;
      void setFrequency(const double& value);

      const double& getSpeed() const;
      void setSpeed(const double& value);

      Matrix<Math::Vector3> compileNormals() const;

   private:
      using LineList = std::list<uint16_t>;

   private:
      void advanceLines(const uint16_t lineIndex);

   protected:
      Size size;



      double frequency;
      double speed;

      double omega;
      DoubleBuffer<Matrix<double>> heightField;

   private:
      int threadCount;
      std::vector<std::thread> threads;
      std::vector<LineList> lineLists;
   };
} // namespace Math

#ifndef MathWaveHPP
#include "MathWave.hpp"
#endif // NOT MathWaveHPP

#endif // NOT MathWaveH
