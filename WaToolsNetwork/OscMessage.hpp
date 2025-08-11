#ifndef OscMessageHPP
#define OscMessageHPP

#include "OscMessage.h"

#include <QColor>
#include <QVariant>

#include <ByteConversion.h>

// see https://hangar.org/wp-content/uploads/2012/01/The-Open-Sound-Control-1.0-Specification-opensoundcontrol.org_.pdf

inline const char OscMessage::paddingChar = 0x00;

inline OscMessage::OscMessage(const QString& path, const QVariantList& values)
   : path(path)
   , values(values)
{
}

inline OscMessage::OscMessage(const QString& path, const QVariant& value)
   : OscMessage(path, QVariantList{value})
{
}

inline OscMessage::OscMessage(const QByteArray& data)
   : path()
   , values()
{
   QList<QByteArray> parts = data.split(',');
   if (2 != parts.size())
      return;

   const QByteArray front = unpad(parts[0]);
   path = QString::fromUtf8(front);

   int backIndex = 0;
   for (; backIndex < parts[1].size(); backIndex++)
   {
      const char value = parts[1][backIndex];
      if (paddingChar == value)
         break;
   }

   const QByteArray types = parts[1].mid(0, backIndex);
   backIndex += 1;
   const int extraIndex = backIndex % 4;
   backIndex += (4 - extraIndex);

   const QByteArray back = parts[1].mid(backIndex - 1);

   int dataIndex = 0;
   for (const char type : types)
   {
      switch (type)
      {
         case 'i':
         {
            const QByteArray data = back.mid(dataIndex, 4);
            dataIndex += 4;
            values += ByteConversion<qint32>::fromBytes(data, true);
            break;
         }
         case 'f':
         {
            const QByteArray data = back.mid(dataIndex, 4);
            dataIndex += 4;
            values += ByteConversion<float>::fromBytes(data, true);
            break;
         }
         case 's':
         default:
         {
            QByteArray data = back.mid(dataIndex, 4);
            dataIndex += 4;
            while (!data.endsWith(paddingChar))
            {
               data += back.mid(dataIndex, 4);
               dataIndex += 4;
            }
            const QByteArray stringData = unpad(data);
            values += QString::fromUtf8(stringData);
            break;
         }
      }
   }
}

inline QByteArray OscMessage::pack()
{
   QByteArray packet = path.toUtf8();
   const int padSizeKey = 4 - packet.size() % 4;
   packet += QByteArray(padSizeKey, 0x00);

   static const int MetaTypeColorList = QMetaType::fromType<QList<QColor>>().id();

   packet += QByteArray(","); // OSC type tag indicator
   for (const QVariant& value : std::as_const(values))
   {
      if (MetaTypeColorList == value.typeId())
      {
         const QList<QColor> colorList = value.value<QList<QColor>>();
         packet += QByteArray(3 * colorList.size(), 'i'); // RGB color
      }
      else
      {
         switch (value.typeId())
         {
            case QMetaType::Bool:
            case QMetaType::Int:
            {
               packet += QByteArray(1, 'i');
               break;
            }
            case QMetaType::Double:
            {
               packet += QByteArray(1, 'f');
               break;
            }
            case QMetaType::QColor:
            {
               packet += QByteArray(3, 'i'); // RGB color
               break;
            }
            case QMetaType::QString:
            default:
            {
               packet += QByteArray(1, 's');
               break;
            }
         }
      }
   }
   addPad(packet);

   for (const QVariant& value : std::as_const(values))
   {
      if (MetaTypeColorList == value.typeId())
      {
         const QList<QColor> colorList = value.value<QList<QColor>>();
         for (const QColor& color : colorList)
         {
            packet += ByteConversion<qint32>::toBytes(color.red(), true);
            packet += ByteConversion<qint32>::toBytes(color.green(), true);
            packet += ByteConversion<qint32>::toBytes(color.blue(), true);
         }
      }
      else
      {
         switch (value.typeId())
         {
            case QMetaType::Bool:
            {
               const bool boolValue = value.toBool();
               packet += ByteConversion<qint32>::toBytes(boolValue ? 1 : 0, true);
               break;
            }
            case QMetaType::Int:
            {
               packet += ByteConversion<qint32>::toBytes(value.toInt(), true);
               break;
            }
            case QMetaType::Double:
            {
               packet += ByteConversion<float>::toBytes(value.toFloat(), true);
               break;
            }
            case QMetaType::QColor:
            {
               const QColor color = value.value<QColor>();
               packet += ByteConversion<qint32>::toBytes(color.red(), true);
               packet += ByteConversion<qint32>::toBytes(color.green(), true);
               packet += ByteConversion<qint32>::toBytes(color.blue(), true);
            }
            case QMetaType::QString:
            default:
            {
               const QString data = value.toString();
               packet += data.toUtf8();
               addPad(packet);
               break;
            }
         }
      }
   }

   return packet;
}

inline const QString& OscMessage::getPath() const
{
   return path;
}

inline const QVariantList& OscMessage::getValues() const
{
   return values;
}

inline void OscMessage::addPad(QByteArray& packet)
{
   const int extraSize = packet.size() % 4;
   packet += QByteArray(4 - extraSize, 0x00);
}

inline QByteArray OscMessage::unpad(QByteArray packet)
{
   while (packet.endsWith(paddingChar))
   {
      packet.chop(1);
   }

   return packet;
}

#endif // NOT OscMessageHPP
