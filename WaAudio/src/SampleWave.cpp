#include "SampleWave.h"

#include <limits>

#include <Bytes.h>
#include <QFile>

#include <QDebug>

const float Sample::Wave::maxValue = static_cast<float>(std::numeric_limits<int16_t>::max());

// 16 bit PCM wav files
// see http://soundfile.sapp.org/doc/WaveFormat/

struct WaveHeader
{
   // RIFF Chunk Descriptor
   uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
   uint32_t chunkSize = 0;                 // RIFF Chunk Size
   uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
};

struct WaveChunkHeader
{
   // "data" sub-chunk
   uint8_t id[4] = {'d', 'a', 't', 'a'}; // "data"  string
   uint32_t dataSize = 0;                // Sampled data length

   QString idName()
   {
      QString text;
      text += QByteArray(1, (char)id[0]);
      text += QByteArray(1, (char)id[1]);
      text += QByteArray(1, (char)id[2]);
      text += QByteArray(1, (char)id[3]);

      return text;
   }
};

struct WaveFmtHeader
{
   // "fmt" sub-chunk
   uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
   uint32_t dataSize = 0;                 // Size of the fmt chunk

   uint16_t audioFormat = 1;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
   uint16_t numChannels = 2;    // Number of channels 1=Mono 2=Stereo
   uint32_t sampleRate = 41000; // Sampling Frequency in Hz
   uint32_t bytesPerSec = 0;    // bytes per second
   uint16_t blockAlign = 0;     // 2=16-bit mono, 4=16-bit stereo
   uint16_t bitsPerSample = 16; // Number of bits per sample
};

bool Sample::Wave::load(const QString& fileName)
{
   meta = Meta();
   interlacedContent = Data();

   QFile file(fileName);
   if (!file.open(QIODevice::ReadOnly))
      return false;

   const QByteArray content = file.readAll();
   size_t cursor = 0;
   file.close();

   auto consume = [&](const size_t length)
   {
      const QByteArray data = content.mid(cursor, length);
      cursor += length;
      return data;
   };

   auto consumeAndCopy = [&](auto& target)
   {
      const int length = sizeof(target);
      const QByteArray data = content.mid(cursor, length);
      cursor += length;

      std::memcpy(&target, data.constData(), length);
   };

   const QByteArray headerData = consume(sizeof(WaveHeader));

   WaveFmtHeader fmtHeader;
   consumeAndCopy(fmtHeader);

   if (fmtHeader.audioFormat != 1 || fmtHeader.bitsPerSample != 16)
      return false;

   meta.noOfChannels = fmtHeader.numChannels;
   meta.sampleRate = fmtHeader.sampleRate;

   while (cursor < content.size())
   {
      WaveChunkHeader header;
      consumeAndCopy(header);

      if ("data" == header.idName())
      {
         const int byteSize = (fmtHeader.bitsPerSample / 8);
         meta.numberOfSamples = header.dataSize / byteSize;

         for (int index = 0; index < meta.numberOfSamples; index++)
         {
            const QByteArray data = consume(byteSize);
            const int iValue = Bytes<uint16_t>::fromBytes(data, true);
            const float value = static_cast<float>(iValue) / maxValue;

            interlacedContent.append(value);
         }
      }
      else
      {
         consume(header.dataSize);
      }
   }

   return true;
}

bool Sample::Wave::save(const QString& fileName)
{
   return false;
   /*
   FILE* wavFile = fopen(fileName.c_str(), "w");
   if (wavFile == nullptr)
      return false;

   {
      WavHeader header;

      header.sampleRate = meta.sampleRate;
      header.numChannels = meta.noOfChannels;
      header.blockAlign = header.numChannels * (header.bitsPerSample / 8);
      header.bytesPerSec = header.sampleRate * header.blockAlign;

      header.dataSize = data.size();
      header.chunkSize = 36 + header.dataSize;

      fwrite(&header, 1, sizeof(WavHeader), wavFile);
   }

   for (const float& value : data)
   {
      const int16_t buffer = static_cast<int16_t>(value * maxValue);
      fwrite(&buffer, 1, sizeof(int16_t), wavFile);
   }

   fclose(wavFile);
   return true;
   */
}
