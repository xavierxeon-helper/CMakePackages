#ifndef MidiParserHPP
#define MidiParserHPP

#include "MidiParser.h"

Midi::Parser::Parser()
   : noteOnFunctionList()
   , noteOffFunctionList()
   , controllerChangeFunctionList()
   , clockTickFunctionList()
   , clockStatusFunctionList()
{
}

void Midi::Parser::processMessage(const Bytes& message)
{
   const bool isSystemEvent = (0xF0 == (message[0] & 0xF0));
   if (!isSystemEvent)
   {
      const Event event = static_cast<Event>(message[0] & 0xF0);
      const Channel channel = 1 + (message[0] & 0x0F);

      if (Event::NoteOn == event)
      {
         const uint8_t midiNote = message[1];
         const Velocity velocity = message[2];
         noteOn(channel, midiNote, velocity);
      }
      else if (Event::NoteOff == event)
      {
         const uint8_t midiNote = message[1];
         noteOff(channel, midiNote);
      }
      else if (Event::ControlChange == event)
      {
         const ControllerMessage controllerMessage = static_cast<ControllerMessage>(message[1]);
         const uint8_t value = message[2];
         controllerChange(channel, controllerMessage, value);
      }
   }
   else
   {
      const Event event = static_cast<Event>(message[0]);

      if (Event::SongPositionPointer == event)
      {
         uint16_t front = static_cast<uint16_t>(message.at(1));
         uint16_t back = static_cast<uint16_t>(message.at(2));

         const uint16_t position = front + (128 * back);
         songPosition(position);
      }
      else if (Event::Clock == event)
      {
         clockTick();
      }
      else if (Event::Start == event)
      {
         clockStatus(Playback::Start);
      }
      else if (Event::Continue == event)
      {
         clockStatus(Playback::Continue);
      }
      else if (Event::Stop == event)
      {
         clockStatus(Playback::Stop);
      }
   }
}

void Midi::Parser::noteOn(const Channel& channel, const uint8_t& midiNote, const Velocity& velocity)
{
   for (const NoteOnFunction& noteOnFunction : noteOnFunctionList)
      noteOnFunction(channel, midiNote, velocity);
}

void Midi::Parser::noteOff(const Channel& channel, const uint8_t& midiNote)
{
   for (const NoteOffFunction& noteOffFunction : noteOffFunctionList)
      noteOffFunction(channel, midiNote);
}

void Midi::Parser::controllerChange(const Channel& channel, const ControllerMessage& controllerMessage, const uint8_t& value)
{
   for (const ControllerChangeFunction& controllerChangeFunction : controllerChangeFunctionList)
      controllerChangeFunction(channel, controllerMessage, value);
}

void Midi::Parser::clockTick()
{
   for (const ClockTickFunction& clockTickFunction : clockTickFunctionList)
      clockTickFunction();
}

void Midi::Parser::clockStatus(const Playback& status)
{
   for (const ClockStatusFunction& clockStatusFunction : clockStatusFunctionList)
      clockStatusFunction(status);
}

void Midi::Parser::songPosition(const uint16_t& position)
{
   for (const SongPositionFunction& songPositionFunction : songPositionFunctionList)
      songPositionFunction(position);
}

#endif // NOT MidiParserHPP
