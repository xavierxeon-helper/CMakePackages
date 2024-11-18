#ifndef MathWaveH
#define MathWaveH

// see https://beltoforion.de/en/recreational_mathematics/2d-wave-equation.php

#include <thread>

#include <DoubleBuffer.h>
#include <MathVector3.h>
#include <Matrix.h>

namespace Math
{
   class Wave
   {
   public:
      Wave(const Size& size, const int& threadCount = 4);

   public:
      void step(const double& time);
      const Matrix<double>& getHeightField() const;
      const Matrix<Math::Vector3>& getNormals() const;

      const Size& getSize() const;

      const double& getFrequency() const;
      void setFrequency(const double& value);

      const double& getSpeed() const;
      void setSpeed(const double& value);

   private:
      using LineList = QList<quint16>;

   private:
      void advanceLines(const quint16 lineIndex);

   protected:
      Size size;

      int threadCount;
      std::vector<std::thread> threads;
      QList<LineList> lineLists;

      double frequency;
      double speed;

      double omega;
      DoubleBuffer<Matrix<double>> heightField;
      Matrix<Math::Vector3> normals;
   };
} // namespace Math

#ifndef MathWaveHPP
#include "MathWave.hpp"
#endif // NOT MathWaveHPP

#endif // NOT MathWaveH
