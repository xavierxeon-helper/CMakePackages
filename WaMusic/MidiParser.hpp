#ifndef MidiParserHPP
#define MidiParserHPP

#include "MidiParser.h"

template <typename ClassType>
void Midi::Parser::onNoteOn(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const uchar&, const Velocity&))
{
   NoteOnFunction noteOnFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   noteOnFunctionList.push_back(noteOnFunction);
}

template <typename ClassType>
void Midi::Parser::onNoteOff(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const uchar&))
{
   NoteOffFunction noteOffFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2);
   noteOffFunctionList.push_back(noteOffFunction);
}

template <typename ClassType>
void Midi::Parser::onControllerChange(ClassType* instance, void (ClassType::*functionPointer)(const Channel&, const ControllerMessage&, const uchar&))
{
   ControllerChangeFunction controllerChangeFunction = std::bind(functionPointer, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
   controllerChangeFunctionList.push_back(controllerChangeFunction);
}

template <typename ClassType>
void Midi::Parser::onClockTick(ClassType* instance, void (ClassType::*functionPointer)())
{
   ClockTickFunction clockTickFunction = std::bind(functionPointer, instance);
   clockTickFunctionList.push_back(clockTickFunction);
}

template <typename ClassType>
void Midi::Parser::onClockStatus(ClassType* instance, void (ClassType::*functionPointer)(const Playback&))
{
   ClockStatusFunction clockStatusFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   clockStatusFunctionList.push_back(clockStatusFunction);
}

template <typename ClassType>
void Midi::Parser::onSongPosition(ClassType* instance, void (ClassType::*functionPointer)(const uint16_t&))
{
   SongPositionFunction songPositionFunction = std::bind(functionPointer, instance, std::placeholders::_1);
   songPositionFunctionList.push_back(songPositionFunction);
}

#endif // NOT MidiParserHPP
