#ifndef XXBusyCursorH
#define XXBusyCursorH

#include "XXGuiExportDef.h"

namespace XX
{
   //! @brief busy cursor as RAII
   /*!
      @details set busy cursor on construction, restore on destruction

      see https://en.cppreference.com/w/cpp/language/raii.html
   */
   //! @ingroup XXGui

   class XXGUI_DECLSPEC BusyCursor
   {
   public:
      BusyCursor();
      ~BusyCursor();
   };
} // namespace XX

#endif // XXBusyCursorH
