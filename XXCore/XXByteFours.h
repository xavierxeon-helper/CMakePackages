#ifndef XXByteFoursH
#define XXByteFoursH

#include "XXCoreExportDef.h"

#include <iostream>

#include <cinttypes>
#include <QDebug>

namespace XX
{
   //! @brief convert a byte into a base 4 representation
   //! @ingroup XXCore

   class XXCORE_DECLSPEC ByteFours
   {
   public:
      enum FoursValue : uint8_t
      {
         O = 0,
         I = 1,
         Z = 2,
         T = 3
      };

   public:
      ByteFours(FoursValue a, FoursValue b, FoursValue c, FoursValue d);
      ByteFours(uint8_t byte = 0);

   public:
      FoursValue value(const FoursValue& index) const;
      operator uint8_t() const;
      QString toString() const;

   private:
      friend XXCORE_DECLSPEC std::ostream& operator<<(std::ostream& out, const ByteFours& bf);
      friend XXCORE_DECLSPEC QDebug operator<<(QDebug stream, const ByteFours& bf);

   private:
      static const uint8_t mask[4];
      FoursValue fours[4];
   };

   XXCORE_DECLSPEC std::ostream& operator<<(std::ostream& out, const ByteFours& bf);
   XXCORE_DECLSPEC QDebug operator<<(QDebug stream, const ByteFours& bf);

} // namespace XX

#endif // NOT XXByteFoursH
