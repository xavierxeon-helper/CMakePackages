#include "XXSampleWave.h"

#include <limits>

#include <QDebug>
#include <QFile>

#include <XXByteConversion.h>

const float XX::Sample::Wave::maxValue = static_cast<float>(std::numeric_limits<int16_t>::max());

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
   uint32_t dataSize = 16;                // Size of the fmt chunk

   uint16_t audioFormat = 1;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
   uint16_t numChannels = 2;    // Number of channels 1=Mono 2=Stereo
   uint32_t sampleRate = 41000; // Sampling Frequency in Hz
   uint32_t bytesPerSec = 0;    // bytes per second
   uint16_t blockAlign = 0;     // 2=16-bit mono, 4=16-bit stereo
   uint16_t bitsPerSample = 16; // Number of bits per sample
};

bool XX::Sample::Wave::load(const QString& fileName)
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
         if (2 != byteSize)
         {
            qDebug() << "Unsupported bits per sample:" << fmtHeader.bitsPerSample;
            return false;
         }
         meta.numberOfSamples = header.dataSize / byteSize;

         for (int index = 0; index < meta.numberOfSamples; index++)
         {
            const QByteArray data = consume(byteSize);
            const int iValue = ByteConversion<int16_t>::fromBytes(data, false);
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

bool XX::Sample::Wave::save(const QString& fileName)
{
   QFile file(fileName);
   if (!file.open(QIODevice::WriteOnly))
      return false;

   auto write = [&](const auto& soure)
   {
      const int length = sizeof(soure);
      QByteArray bytes(length, 0);

      std::memcpy(bytes.data(), &soure, length);

      file.write(bytes);
   };

   QByteArray data;
   for (const float& value : interlacedContent)
   {
      const int16_t iValue = static_cast<int16_t>(value * maxValue);
      const QByteArray bytes = ByteConversion<int16_t>::toBytes(iValue, false);
      data.append(bytes);
   }

   WaveFmtHeader fmtHeader;

   fmtHeader.sampleRate = meta.sampleRate;
   fmtHeader.numChannels = meta.noOfChannels;
   fmtHeader.blockAlign = fmtHeader.numChannels * (fmtHeader.bitsPerSample / 8);
   fmtHeader.bytesPerSec = fmtHeader.sampleRate * fmtHeader.blockAlign;

   WaveChunkHeader chunkHeader;

   chunkHeader.dataSize = data.size();

   WaveHeader header;
   header.chunkSize = 36 + chunkHeader.dataSize;

   write(header);
   write(fmtHeader);
   write(chunkHeader);

   file.write(data);

   return true;
}
