#ifndef MidiParserH
#define MidiParserH

#include <functional>

#include "MidiCommon.h"
#include "Note.h"

namespace Midi
{
   class Parser
   {
   public:
      using NoteOnFunction = std::function<void(const Channel& channel, const uint8_t& midiNote, const Velocity& velocity)>;
      using NoteOffFunction = std::function<void(const Channel& channel, const uint8_t& midiNote)>;
      using ControllerChangeFunction = std::function<void(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)>;
      using ClockTickFunction = std::function<void()>;
      using ClockStatusFunction = std::function<void(const Playback& status)>;
      using SongPositionFunction = std::function<void(const uint16_t& position)>;

   public:
      Parser();

   public:
      virtual void processMessage(const Bytes& message);

      // register callback functions
      template <typename ClassType>
      void onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const uint8_t&, const Velocity&));

      template <typename ClassType>
      void onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const uint8_t&));

      template <typename ClassType>
      void onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const ControllerMessage&, const uint8_t&));

      template <typename ClassType>
      void onClockTick(ClassType* instance, void (ClassType::*functionPointer)());

      template <typename ClassType>
      void onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&));

      template <typename ClassType>
      void onSongPosition(ClassType* instance, void (ClassType::*functionPointer)(const uint16_t&));

   protected:
      // default executes callback functions
      virtual void noteOn(const Channel& channel, const uint8_t& midiNote, const Velocity& velocity);
      virtual void noteOff(const Channel& channel, const uint8_t& midiNote);
      virtual void controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value);
      virtual void clockTick();
      virtual void clockStatus(const Playback& status);
      virtual void songPosition(const uint16_t& position);

   private:
      std::vector<NoteOnFunction> noteOnFunctionList;
      std::vector<NoteOffFunction> noteOffFunctionList;
      std::vector<ControllerChangeFunction> controllerChangeFunctionList;
      std::vector<ClockTickFunction> clockTickFunctionList;
      std::vector<ClockStatusFunction> clockStatusFunctionList;
      std::vector<SongPositionFunction> songPositionFunctionList;
   };
} // namespace Midi

#ifndef MidiParserHPP
#include "MidiParser.hpp"
#endif // NOT MidiParserHPP

#endif // NOT MidiParserH
