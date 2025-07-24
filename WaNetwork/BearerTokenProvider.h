#ifndef BearerTokenProviderH
#define BearerTokenProviderH

#include <QObject>

class BearerTokenProvider : public QObject
{
   // do not use Q_OBJECT
   // this file will not be moc'ed automatically

public:
   BearerTokenProvider(QObject* parent);

public:
   const QByteArray& getBearerToken() const;
   bool isEmpty() const;

   void setBearerToken(const QByteArray& token);
   virtual bool update();

private:
   QByteArray bearerToken;
};
#ifndef BearerTokenProviderHPP
#include "BearerTokenProvider.hpp"
#endif // NOT BearerTokenProviderHPP

#endif // NOT BearerTokenProviderH
