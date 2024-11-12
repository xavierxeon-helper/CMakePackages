#ifndef LogFileH
#define LogFileH

#include "IOChannel.h"

class LogFile : public IOChannel::Target
{
public:
   LogFile(const QString& fileName);
   ~LogFile();

public:
   static QTextStream stream();

public:
   void print(const QString& text, int channelId) override;

private:
   static LogFile* me;
   IOChannel* channel;
};

#ifndef LogFileHPP
#include "LogFile.hpp"
#endif // NOT LogFileHPP

#endif // NOT LogFileH
