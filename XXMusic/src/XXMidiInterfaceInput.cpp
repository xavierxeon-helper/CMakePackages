#include "XXMidiInterfaceInput.h"

XX::Midi::Interface::Input::Input()
   : Parser()
   , passthroughList()
{
}

XX::Midi::Interface::Input::~Input()
{
   // do nothing
}

void XX::Midi::Interface::Input::open()
{
   // do nothing
}

void XX::Midi::Interface::Input::close()
{
   // do nothing
}

bool XX::Midi::Interface::Input::isOpen() const
{
   return false;
}

void XX::Midi::Interface::Input::addPassThroughInterface(XX::Midi::Interface::Output* passthrough)
{
   passthroughList.push_back(passthrough);
}
