#ifndef ShallowCryptHPP
#define ShallowCryptHPP

#include "ShallowCrypt.h"

#include <QRandomGenerator>

inline ShallowCrypt::ShallowCrypt(QByteArray key, QCryptographicHash::Algorithm algorithm)
   : key(key)
   , algorithm(algorithm)
   , checkLength(0)
{
   checkLength = QCryptographicHash::hashLength(algorithm);
}

inline QByteArray ShallowCrypt::bury(const QString& plainText) const
{
   if (key.isEmpty())
      return plainText.toUtf8();

   QByteArray data = plainText.toUtf8();
   data = randomByte() + addCheckAndScramble(data); // add random byte

   encrypt(data);
   return data.toBase64();
}

inline QString ShallowCrypt::revive(const QByteArray encryptedText) const
{
   if (key.isEmpty())
      return QString::fromUtf8(encryptedText);

   QByteArray data = QByteArray::fromBase64(encryptedText);
   decrypt(data);

   data = data.mid(1); // discard random byte
   data = unscrambleAndVerify(data);

   return QString::fromUtf8(data);
}

inline void ShallowCrypt::encrypt(QByteArray& data) const
{
   if (key.isEmpty())
      return;

   const quint32 length = data.count();
   quint8 lastChar = 0;

   for (quint32 pos = 0; pos < length; pos++)
   {
      const quint8 keyByte = key.at(pos % key.length());

      quint8 current = data.at(pos);
      lastChar = current ^ keyByte ^ lastChar;
      data[pos] = lastChar;
   }
}

inline void ShallowCrypt::decrypt(QByteArray& data) const
{
   if (key.isEmpty())
      return;

   const quint32 length = data.count();
   quint8 lastChar = 0;

   for (quint32 pos = 0; pos < length; pos++)
   {
      const quint8 keyByte = key.at(pos % key.length());

      quint8 current = data.at(pos);
      data[pos] = current ^ lastChar ^ keyByte;
      lastChar = current;
   }
}

inline QByteArray ShallowCrypt::randomByte() const
{
   const quint8 random = QRandomGenerator::global()->bounded(255);
   const QByteArray byte = QByteArray(reinterpret_cast<const char*>(&random), 1);

   return byte;
}

inline QByteArray ShallowCrypt::addCheckAndScramble(const QByteArray& payload) const
{
   // create check
   const QByteArray check = QCryptographicHash::hash(payload, algorithm);

   // scramble check with payload
   QByteArray content = check + payload;
   content = rotateUnevenBytes(content);

   return qCompress(content, 9); // less to store and false trail
}

inline QByteArray ShallowCrypt::unscrambleAndVerify(const QByteArray& data) const
{
   QByteArray content = qUncompress(data); // uncompress
   content = rotateUnevenBytes(content);

   const QByteArray target = content.mid(0, checkLength); // the integrity hash
   const QByteArray payload = content.mid(checkLength);   // the actual data

   const QByteArray check = QCryptographicHash::hash(payload, algorithm);
   if (target != check)
      return QByteArray();

   return payload;
}

inline QByteArray ShallowCrypt::rotateUnevenBytes(const QByteArray& data) const
{
   const quint32 length = data.length();
   const quint32 halfLength = [&]()
   {
      if (0 != (length % 2))
         return (length + 1) / 2;

      return length / 2;
   }();

   QByteArray content = data;
   for (quint32 frontIndex = 0; frontIndex < halfLength; frontIndex += 2)
   {
      const quint32 backIndex = halfLength + frontIndex;
      if (backIndex >= length)
         break;

      content[frontIndex] = data[backIndex];
      content[backIndex] = data[frontIndex];
   }

   return content;
}

#endif // ShallowCryptHPP
