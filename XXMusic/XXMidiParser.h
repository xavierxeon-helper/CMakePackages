#ifndef XXMidiParserH
#define XXMidiParserH

#include "XXMusicExportDef.h"

#include <functional>
#include <vector>

#include "XXMidiCommon.h"

namespace XX
{
   namespace Midi
   {
      //! @brief midi event parser
      //! @ingroup XXMusic

      class XXMUSIC_DECLSPEC Parser
      {
      public:
         using NoteOnFunction = std::function<void(const Channel& channel, const uchar& midiNote, const Velocity& velocity)>;
         using NoteOffFunction = std::function<void(const Channel& channel, const uchar& midiNote, const Velocity& velocity)>;
         using ControllerChangeFunction = std::function<void(const Channel& channel, const ControllerMessage& controllerMessage, const uchar& value)>;
         using ClockTickFunction = std::function<void()>;
         using ClockStatusFunction = std::function<void(const Playback& status)>;
         using SongPositionFunction = std::function<void(const uint16_t& position)>;

      public:
         Parser();

      public:
         virtual void processMessage(const std::vector<uchar>& message);

         // register callback functions
         template <typename ClassType>
         void onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const uchar&, const Velocity&));

         template <typename ClassType>
         void onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const uchar&, const Velocity&));

         template <typename ClassType>
         void onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const ControllerMessage&, const uchar&));

         template <typename ClassType>
         void onClockTick(ClassType* instance, void (ClassType::*functionPointer)());

         template <typename ClassType>
         void onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&));

         template <typename ClassType>
         void onSongPosition(ClassType* instance, void (ClassType::*functionPointer)(const uint16_t&));

      protected:
         // default executes callback functions
         virtual void noteOn(const Channel& channel, const uchar& midiNote, const Velocity& velocity);
         virtual void noteOff(const Channel& channel, const uchar& midiNote, const Velocity& velocity);
         virtual void controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uchar& value);
         virtual void clockTick();
         virtual void clockStatus(const Playback& status);
         virtual void songPosition(const uint16_t& position);

      private:
         QList<NoteOnFunction> noteOnFunctionList;
         QList<NoteOffFunction> noteOffFunctionList;
         QList<ControllerChangeFunction> controllerChangeFunctionList;
         QList<ClockTickFunction> clockTickFunctionList;
         QList<ClockStatusFunction> clockStatusFunctionList;
         QList<SongPositionFunction> songPositionFunctionList;
      };
   } // namespace Midi
} // namespace XX

#ifndef XXMidiParserHPP
#include "XXMidiParser.hpp"
#endif // NOT XXMidiParserHPP

#endif // NOT XXMidiParserH
