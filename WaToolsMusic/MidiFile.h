#ifndef MidiFileH
#define MidiFileH

#include "WaToolsMusicExportDef.h"

#include <QList>
#include <QMap>

#include "MidiCommon.h"
#include "TimeCode.h"

namespace Midi
{
   class WATOOLSMUSIC_DECLSPEC Sequence
   {
   public:
      using Tick = uint64_t;
      using TimeMessageMap = QMap<Tick, MessageList>;

      struct Info
      {
         Tick maxTick = 0;
         uint64_t barCounter = 0;
         uint16_t bpm = 0;
         uint32_t minutes = 0;
         uchar seconds = 0;
      };

      struct Track
      {
         Tick maxTick = 0;
         std::string name;
         bool isMonophonic = false;

         TimeMessageMap messageMap;

         using List = QList<Track>;
      };

   public:
      Sequence();

   public:
      Info compileInfo() const;
      const Track::List& getTrackList() const;
      uint64_t compileBarCounter(uint64_t trackIndex) const;

      TimeCode::Duration fromTick(const Tick& tick);
      Tick toTick(const TimeCode::Duration& duration, const double& precentageToNextBeat = 0);

   protected:
      uint16_t ticksPer16;
      uint64_t uSecsPerQuarter; // only relevant to get file bpm
      Track::List trackList;
   };

   namespace File
   {
      // see http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html

      class WATOOLSMUSIC_DECLSPEC Reader : public Sequence
      {
      public:
         Reader(const Bytes& content);

      private:
         struct Chunk
         {
            std::string id;
            Bytes data;

            using List = QList<Chunk>;
         };

      private:
         // workflow
         void readHeader(const Chunk& headerChunk);
         void readTrack(const Chunk& trackChunk);
         MetaEvent readMetaEventAndAdvanceCursor(const Bytes& trackChunkData, uint64_t& cursor, Track* track);
         uchar compileMidiEventLength(const uchar marker) const;

         uint64_t variableLength(const Bytes& data, uint64_t& cursor) const;
      };
   } // namespace File
} // namespace Midi

#endif // NOT MidiFileH
