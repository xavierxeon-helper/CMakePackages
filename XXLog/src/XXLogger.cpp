#include "XXLogger.h"

#include <QIODevice>

// proxy

class XX::Logger::Target::StreamProxy : public QIODevice
{
public:
   StreamProxy(const QColor& color);

private:
   qint64 readData(char* data, qint64 maxSize) override;
   qint64 writeData(const char* data, qint64 maxSize) override;

private:
   const QColor color;
};

XX::Logger::Target::StreamProxy::StreamProxy(const QColor& color)
   : QIODevice()
   , color(color)
{
   open(QIODevice::WriteOnly);
}

qint64 XX::Logger::Target::StreamProxy::readData(char* data, qint64 maxSize)
{
   Q_UNUSED(data)
   Q_UNUSED(maxSize)

   return 0;
}

qint64 XX::Logger::Target::StreamProxy::writeData(const char* data, qint64 maxSize)
{
   if (!master)
      return maxSize;

   const QString text = QString::fromUtf8(data);
   master->print(text, color);

   return maxSize;
}

// stream

QTextStream XX::Logger::stream(const Qt::GlobalColor& color)
{
   using ProxyMap = QMap<Qt::GlobalColor, Target::StreamProxy*>;
   static ProxyMap proxyMap;
   if (!proxyMap.contains(color))
   {
      Target::StreamProxy* proxy = new Target::StreamProxy(QColor(color));
      proxyMap.insert(color, proxy);
   }

   Target::StreamProxy* proxy = proxyMap.value(color);
   return QTextStream(proxy);
}

// target

XX::Logger::Target* XX::Logger::Target::master = nullptr;

XX::Logger::Target::Target(int stackSize)
   : others()
   , stackSize(stackSize)
   , buffer()
{
   if (master)
      master->others.append(this);
   else
      master = this;
}

XX::Logger::Target::~Target()
{
   if (master == this)
   {
      if (master->others.isEmpty())
         master = nullptr;
      else
         master = master->others.takeFirst();
   }
   else
   {
      master->others.removeAll(this);
   }
}

void XX::Logger::Target::clear()
{
   master->buffer.clear();

   update(buffer);
   for (Target* target : others)
      target->update(buffer);
}

void XX::Logger::Target::print(const QString& text, const QColor& color)
{
   buffer.append({QDateTime::currentDateTime(), text, color});

   while (buffer.size() > stackSize)
      buffer.removeFirst();

   update(buffer);
   for (Target* target : others)
      target->update(buffer);
}
