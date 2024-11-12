#ifndef LogFileHPP
#define LogFileHPP

#include "LogFile.h"

inline LogFile* LogFile::me = nullptr;

inline LogFile::LogFile(const QString& fileName)
   : IOChannel::Target()
   , channel(nullptr)
{
   me = this;
   channel = new IOChannel(this, 0);
}

inline LogFile::~LogFile()
{
   delete channel;
   channel = nullptr;

   me = nullptr;
}

inline QTextStream LogFile::stream()
{
   if (!me)
      return QTextStream();

   return QTextStream(me->channel);
}

inline void LogFile::print(const QString& text, int channelId)
{
   qDebug() << text;
}

#endif // NOT LogFileHPP
