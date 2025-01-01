#ifndef IOChannelH
#define IOChannelH

#include <QIODevice>
#include <QString>

class IOChannel : public QIODevice
{
   // do not use Q_OBJECT
   // this file will not be moc'ed

public:
   using PrintFunction = std::function<void(const QString& message)>;

public:
   IOChannel(QObject* parent, PrintFunction printFunction);

public:
   QTextStream stream();

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
