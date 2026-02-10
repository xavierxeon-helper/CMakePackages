#ifndef PopulatedMenuBarH
#define PopulatedMenuBarH

#include "WaToolsApplicationExportDef.h"
#include <QMenuBar>

namespace Populated
{
   class WATOOLSAPPLICATION_DECLSPEC MenuBar : public QMenuBar
   {
      Q_OBJECT
      Q_PROPERTY(QString menuName READ getMenuName WRITE setMenuName NOTIFY menuNameChanged)

   public:
      explicit MenuBar(QWidget* parent = nullptr);

   signals:
      void menuNameChanged();

   public:
      const QString& getMenuName() const;
      void setMenuName(const QString& name);

   private:
      QString menuName;
   };
} // namespace Populated

#endif // NOT PopulatedMenuBarH
