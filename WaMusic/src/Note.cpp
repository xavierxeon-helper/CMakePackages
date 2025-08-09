#include "Note.h"

#include <Range.h>

#include <QMap>

const Note Note::zeroNote = Note();

const Note::List Note::availableNotes = []()
{
   Note::List noteList;
   noteList.push_back(zeroNote);

   using NameMap = QMap<Note::Value, QString>;
   const NameMap nameMap = {
      {C, "C"},
      {Cs, "C#"},
      {D, "D"},
      {Ds, "D#"},
      {E, "E"},
      {F, "F"},
      {Fs, "F#"},
      {G, "G"},
      {Gs, "G#"},
      {A, "A"},
      {As, "A#"},
      {B, "B"},
   };

   const QList<float> noteAFreq = []()
   {
      float value = 0.25 * 55.0;

      QList<float> freq;
      freq.push_back(value);

      for (uchar index = 1; index < 21; index++)
      {
         value *= 2;
         freq.push_back(value);
      }
      return freq;
   }();

   auto fillNoteList = [&]()
   {
      uchar midiValue = 24;
      for (Octave octave = 0; octave < 20; octave++)
      {
         for (uchar voltageIndex = 0; voltageIndex < 12; voltageIndex++)
         {
            const Value value = static_cast<Value>(voltageIndex);
            const QString name = nameMap.value(value) + QString::number(octave);

            const float voltage = octave + (voltageIndex / 12.0);
            const uchar freqOctave = static_cast<uchar>(voltage + 0.25);
            const float rest = (voltage - freqOctave) + 0.25;
            const float frequency = noteAFreq[freqOctave] * pow(2, rest);

            Note note(name, value, octave, frequency, voltage, midiValue);
            midiValue++;

            noteList.push_back(note);
            if (note.frequency > 20000)
               return;
         }
      }
   };

   fillNoteList();
   return noteList;
}();

const uchar Note::maxNoteIndex = availableNotes.size() - 1;

// note

Note::Note()
   : name("Z0")
   , value(Note::Invalid)
   , octave(0)
   , frequency(-1.0f)
   , voltage(0.0f)
   , midiValue(0)
{
}

bool Note::operator==(const Note& other) const
{
   return name == other.name;
}

bool Note::operator!=(const Note& other) const
{
   return name != other.name;
}

bool Note::operator<(const Note& other) const
{
   const int indexThis = availableNotes.indexOf(*this);
   const int indexOther = availableNotes.indexOf(other);

   return indexThis < indexOther;
}

const Note& Note::fromVoltage(float voltage)
{
   if (0.0f > voltage)
      return zeroNote;

   const float value = Range::clamp<float>(voltage, 0.0f, 10.0f) * 12.0;
   const uchar index = 1 + static_cast<uchar>(value);
   if (index >= maxNoteIndex)
      return availableNotes[maxNoteIndex];
   else
      return availableNotes[index];
}

const Note& Note::fromMidi(uchar midi)
{
   if (0 == midi)
      return zeroNote;

   const uchar index = 1 + midi - availableNotes.at(1).midiValue;
   if (index >= maxNoteIndex)
      return availableNotes[maxNoteIndex];
   else
      return availableNotes[index];
}

const Note& Note::fromFrequency(float frequency)
{
   static const float minFrequency = availableNotes[1].frequency;
   static const float maxFrequency = availableNotes[maxNoteIndex].frequency;

   if (frequency < minFrequency)
      return Note::zeroNote;

   frequency = Range::clamp<float>(frequency, minFrequency, maxFrequency);
   const float expo = frequency / minFrequency;
   const float voltage = log2(expo);

   const Note& note = fromVoltage(voltage);
   return note;
}

Note Note::up() const
{
   const int index = availableNotes.indexOf(*this);
   if (index < maxNoteIndex)
      return availableNotes[index + 1];

   return zeroNote;
}

Note Note::down() const
{
   const int index = availableNotes.indexOf(*this);
   if (index > 0)
      return availableNotes[index - 1];

   return zeroNote;
}

bool Note::isWhiteKey() const
{
   static const QList<Note::Value> whiteKeys = {C, D, E, F, G, A, B};
   return whiteKeys.contains(value);
}

bool Note::isBlackKey() const
{
   static const QList<Note::Value> blackKeys = {Cs, Ds, Fs, Gs, As};
   return blackKeys.contains(value);
}

bool Note::isVaid() const
{
   return (*this != zeroNote);
}

const QString& Note::getName() const
{
   return name;
}
const Note::Value& Note::getValue() const
{
   return value;
}
const Note::Octave& Note::getOctave() const
{
   return octave;
}
const float& Note::getFrequency() const
{
   return frequency;
}
const float& Note::getVoltage() const
{
   return voltage;
}
const uchar& Note::getMidiValue() const
{
   return midiValue;
}

Note::Note(QString name, Value value, Octave octave, float frequency, float voltage, uchar midiValue)
   : name(name)
   , value(value)
   , octave(octave)
   , frequency(frequency)
   , voltage(voltage)
   , midiValue(midiValue)
{
}
