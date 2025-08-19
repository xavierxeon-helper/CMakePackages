#ifndef OscMessageH
#define OscMessageH

#include "WaToolsNetworkExportDef.h"

#include <QVariant>

class WATOOLSNETWORK_DECLSPEC OscMessage
{
public:
   OscMessage() = delete;
   OscMessage(const QString& path, const QVariant& value);
   OscMessage(const QString& path, const QVariantList& values);
   OscMessage(const QByteArray& data); // from received data

public:
   QByteArray pack(); // to send data

   const QString& getPath() const;
   const QVariantList& getValues() const;

private:
   void addPad(QByteArray& packet);
   QByteArray unpad(QByteArray packet);

private:
   static const char paddingChar;
   QString path;
   QVariantList values;
};

#endif // NOT OscMessageH
