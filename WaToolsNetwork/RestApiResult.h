#ifndef RestApiResultH
#define RestApiResultH

#include "WaToolsNetworkExportDef.h"

#include <QByteArray>
#include <QJsonObject>

namespace RestApi
{
   struct WATOOLSNETWORK_DECLSPEC ResultRaw
   {
      QByteArray raw;
      int statusCode = 0;
   };

   struct WATOOLSNETWORK_DECLSPEC Result : ResultRaw
   {
      QJsonObject json;

      void parseJson();
   };
} // namespace RestApi

#endif // NOT RestApiResultH
