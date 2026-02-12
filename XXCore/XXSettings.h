#ifndef XXSettingsH
#define XXSettingsH

#include "XXCoreExportDef.h"

#include <QJsonArray>
#include <QJsonObject>

namespace XX
{
   class XXCORE_DECLSPEC Settings
   {
   public:
      Settings();
      ~Settings();

   public:
      static QString compileFileName();

      void setValue(const QString& key, const QVariant& value);
      QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
      void clearValue(const QString& key);

   private:
      struct PathKey
      {
         QStringList path;
         QString key;
      };

   private:
      PathKey compilePathKey(const QString& key) const;

      QJsonValue getPathValue(const PathKey& pathKey) const;
      void setPathValue(const PathKey& pathKey, const QJsonValue& value);

      void clearPath(const PathKey& pathKey);

   private:
      static QString fileName;
      static int instanceCount;
      static QJsonObject data;

      static const QString ByteArrayMarker;
   };
} // namespace XX

#endif // NOT XXSettingsH
