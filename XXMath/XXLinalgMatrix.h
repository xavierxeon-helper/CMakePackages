#ifndef XXLinalgMatrixH
#define XXLinalgMatrixH

namespace XX
{
   namespace Linalg
   {
      class Matrix
      {
      public:
         Matrix();

      public:
         Matrix inverse() const;
         Matrix transpose() const;
         double determinant() const;
      };
   } // namespace Linalg
} // namespace XX

#endif // NOT XXLinalgMatrixH
