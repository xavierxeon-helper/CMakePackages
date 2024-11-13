#ifndef MatrixH
#define MatrixH

template <typename DataType>
class Matrix : public QList<QList<DataType>>
{
public:
   Matrix(const quint16& width, const quint16& height, const DataType& initialValue);

public:
   const quint16& getWidth() const;
   const quint16& getHeight() const;

private:
   quint16 width;
   quint16 height;
};

#ifndef MatrixHPP
#include "Matrix.hpp"
#endif // NOT MatrixHPP

#endif // NOT MatrixH
