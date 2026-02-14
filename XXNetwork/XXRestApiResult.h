#ifndef XXRestApiResultH
#define XXRestApiResultH

#include "XXNetworkExportDef.h"

#include <QByteArray>
#include <QJsonObject>

namespace XX
{
   namespace RestApi
   {
      //! @brief  REST API results
      //! @ingroup XXNetwork

      struct XXNETWORK_DECLSPEC ResultRaw
      {
         QByteArray raw;
         int statusCode = 0;
      };

      //! @brief  REST API with json content
      //! @details json content is only parsed when parseJson() is called
      //! @ingroup XXNetwork

      struct XXNETWORK_DECLSPEC Result : ResultRaw
      {
         QJsonObject json;

         void parseJson();
      };
   } // namespace RestApi
} // namespace XX

#endif // NOT XXRestApiResultH
