#include "RestApiResult.h"

#include <FileTools.h>

void RestApi::Result::parseJson()
{
   json = FileTools::parseBytes(raw);
}
