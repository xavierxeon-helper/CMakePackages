#ifndef MidiInterfaceInputH
#define MidiInterfaceInputH

#include "XXMidiParser.h"
#include "XXMusicExportDef.h"

namespace Midi
{
   namespace Interface
   {
      class Output;

      class XXMUSIC_DECLSPEC Input : public Parser
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
         QList<Interface::Output*> passthroughList;
      };
   } // namespace Interface
} // namespace Midi

#endif // NOT MidiInterfaceInputH
