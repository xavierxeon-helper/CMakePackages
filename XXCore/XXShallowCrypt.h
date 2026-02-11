#ifndef ShallowCryptH
#define ShallowCryptH

#include "XXCoreExportDef.h"

#include <QCryptographicHash>
#include <QString>
#include <QSysInfo>

/**  
uses a simple XOR cipher + some additional obfuscations
see https://en.wikipedia.org/wiki/XOR_cipher
THIS IS NOT A SAFE ENCRYPTION!
*/

class XXCORE_DECLSPEC ShallowCrypt
{
public:
   /// no key => no encryption!
   ShallowCrypt(QByteArray key = QSysInfo::machineUniqueId(), QCryptographicHash::Algorithm algorithm = QCryptographicHash::Sha1);

public:
   QByteArray bury(const QString& plainText) const;
   QString revive(const QByteArray encryptedText) const;

private:
   void encrypt(QByteArray& data) const;
   void decrypt(QByteArray& data) const;
   QByteArray randomByte() const;
   QByteArray addCheckAndScramble(const QByteArray& payload) const;
   QByteArray unscrambleAndVerify(const QByteArray& data) const;
   QByteArray rotateUnevenBytes(const QByteArray& data) const;

private:
   QByteArray key;
   QCryptographicHash::Algorithm algorithm;
   int checkLength;
};

#endif // NOT ShallowCryptH
