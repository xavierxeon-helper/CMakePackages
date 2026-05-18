#ifndef MultimediaVideoWriterHPP
#define MultimediaVideoWriterHPP

#include "MultimediaVideoWriter.h"

template <typename ClassType>
void Multimedia::VideoWriter::registerSetupFunction(ClassType* instance, void (ClassType::*function)())
{
   setupFunction = std::bind(function, instance);
}

#endif // NOT MultimediaVideoWriterHPP