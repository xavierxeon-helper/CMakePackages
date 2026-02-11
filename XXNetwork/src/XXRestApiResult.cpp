#include "XXRestApiResult.h"

#include <XXFileTools.h>

void XX::RestApi::Result::parseJson()
{
   if (raw.isEmpty())
      json = QJsonObject{};
   else
      json = FileTools::parseBytes(raw);
}
