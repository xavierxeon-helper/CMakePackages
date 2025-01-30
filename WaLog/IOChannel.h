#ifndef IOChannelH
#define IOChannelH

#include <QIODevice>
#include <QString>

class IOChannel : public QIODevice
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   using PrintFunction = std::function<void(const QString& message)>;

public:
   IOChannel(QObject* parent);
   IOChannel(QObject* parent, PrintFunction printFunction);

public:
   QTextStream stream();
   void setup(PrintFunction printFunction);

private:
   qint64 readData(char* data, qint64 maxSize) override;
   qint64 writeData(const char* data, qint64 maxSize) override;

private:
   PrintFunction printFunction;
};

#ifndef IOChannelHPP
#include "IOChannel.hpp"
#endif // NOT IOChannelHPP

#endif // NOT IOChannelH
