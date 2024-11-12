#ifndef IOChannelH
#define IOChannelH

#include <QIODevice>
#include <QString>

class IOChannel : public QIODevice
{
   // do not use Q_OBJECT !

public:
   struct Target
   {
      virtual void print(const QString& text, int chanelId) = 0;
   };

public:
   IOChannel(Target* target, int channelId);

private:
   qint64 readData(char* data, qint64 maxSize) override;
   qint64 writeData(const char* data, qint64 maxSize) override;

private:
   Target* target;
   int channelId;
};

#ifndef IOChannelHPP
#include "IOChannel.hpp"
#endif // NOT IOChannelHPP

#endif // NOT IOChannelH
