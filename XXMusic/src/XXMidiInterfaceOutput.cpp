#include "XXMidiInterfaceOutput.h"

XX::Midi::Interface::Output::Output()
{
}

XX::Midi::Interface::Output::~Output()
{
   // do nothing
}

void XX::Midi::Interface::Output::open()
{
   // do nothing
}

void XX::Midi::Interface::Output::close()
{
   // do nothing
}

bool XX::Midi::Interface::Output::isOpen() const
{
   return false;
}

void XX::Midi::Interface::Output::sendNoteOn(const Channel& channel, const Note& note, const Velocity& velocity)
{
   //qDebug() << "NOTE ON" << QString::fromStdString(note.name);

   Bytes buffer;

   buffer.append((Event::NoteOn | (channel - 1)));
   buffer.append(note.getMidiValue());
   buffer.append(velocity);

   sendBuffer(buffer);
}

void XX::Midi::Interface::Output::sendNoteOff(const Channel& channel, const Note& note)
{
   //qDebug() << "NOTE OFF" << QString::fromStdString(note.name);

   Bytes buffer;

   buffer.append((Event::NoteOff | (channel - 1)));
   buffer.append(note.getMidiValue());
   buffer.append(127);

   sendBuffer(buffer);
}

void XX::Midi::Interface::Output::sendControllerChange(const Channel& channel, const ControllerMessage& cotrollerMessage, const uchar& value)
{
   Bytes buffer;

   buffer.append((Event::ControlChange | (channel - 1)));
   buffer.append(cotrollerMessage);
   buffer.append(value);

   sendBuffer(buffer);
}
