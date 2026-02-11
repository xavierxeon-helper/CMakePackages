#ifndef NoteH
#define NoteH

#include "XXMusicExportDef.h"
#include <QObject>

#include <QList>

class XXMUSIC_DECLSPEC Note
{
   Q_GADGET

public:
   using List = QList<Note>;
   using Octave = uchar;

   enum Value : uchar //
   {
      C = 0,
      Cs,
      D,
      Ds,
      E,
      F,
      Fs,
      G,
      Gs,
      A,
      As,
      B,
      Invalid
   };
   Q_ENUM(Value)

   static const QString sharpSymbol;
   static const QString flatSymbol;

   static const Note zeroNote;       // an invalid note
   static const List availableNotes; // includes zero note
   static const uchar maxNoteIndex;  // size of availableNotes

public:
   Note();

public:
   bool operator==(const Note& other) const;
   bool operator!=(const Note& other) const;
   bool operator<(const Note& other) const;

public:
   static const Note& fromVoltage(float voltage);
   static const Note& fromMidi(uchar midi);
   static const Note& fromFrequency(float frequency);
   Note up() const;
   Note down() const;
   bool isWhiteKey() const;
   bool isBlackKey() const;
   bool isValid() const; // note is not zero note
   const QString& getName() const;
   const Value& getValue() const;
   const Octave& getOctave() const;
   const float& getFrequency() const;
   const float& getVoltage() const;
   const uchar& getMidiValue() const;

private:
   QString name;
   Value value;
   Octave octave;
   float frequency;
   float voltage;
   uchar midiValue;

private:
   Note(QString name, Value value, Octave octave, float frequency, float voltage, uchar midiValue);
};

#endif // NoteH
