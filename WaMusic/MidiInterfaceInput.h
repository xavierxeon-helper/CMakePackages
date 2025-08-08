#ifndef MidiInterfaceInputH
#define MidiInterfaceInputH

#include "MidiParser.h"

#include <functional>

#include "MidiCommon.h"
#include "Note.h"

namespace Midi
{
   namespace Interface
   {
      class Output;

      class Input : public Parser
      {
      public:
         Input();
         virtual ~Input();

      public:
         virtual void open();
         virtual void close();
         virtual bool isOpen() const;

         void addPassThroughInterface(Interface::Output* passthrough);

      protected:
         std::vector<Interface::Output*> passthroughList;
      };
   } // namespace Interface
} // namespace Midi

#endif // NOT MidiInterfaceInputH
