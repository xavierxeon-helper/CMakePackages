#include "XXRestApiResult.h"

#include <XXFileTools.h>

void RestApi::Result::parseJson()
{
   if (raw.isEmpty())
      json = QJsonObject{};
   else
      json = FileTools::parseBytes(raw);
}
