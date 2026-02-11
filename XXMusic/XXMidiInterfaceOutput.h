#ifndef MidiInterfaceOutputH
#define MidiInterfaceOutputH

#include "XXMusicExportDef.h"

#include "XXMidiCommon.h"
#include "XXNote.h"

namespace Midi
{
   namespace Interface
   {
      class XXMUSIC_DECLSPEC Output
      {
      public:
         Output();
         virtual ~Output();

      public:
         virtual void open();
         virtual void close();
         virtual bool isOpen() const;

         void sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity);
         void sendNoteOff(const Midi::Channel& channel, const Note& note);
         void sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uchar& value);

         virtual void sendBuffer(const Bytes& message) = 0;
      };

   } // namespace Interface
} // namespace Midi

#endif // NOT MidiInterfaceOutputH
