#ifndef XXRestApiResultH
#define XXRestApiResultH

#include "XXNetworkExportDef.h"

#include <QByteArray>
#include <QJsonObject>

namespace RestApi
{
   struct XXNETWORK_DECLSPEC ResultRaw
   {
      QByteArray raw;
      int statusCode = 0;
   };

   struct XXNETWORK_DECLSPEC Result : ResultRaw
   {
      QJsonObject json;

      void parseJson();
   };
} // namespace RestApi

#endif // NOT XXRestApiResultH
