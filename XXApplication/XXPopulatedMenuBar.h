#ifndef XXPopulatedMenuBarH
#define XXPopulatedMenuBarH

#include "XXApplicationExportDef.h"
#include <QMenuBar>

namespace Populated
{
   class XXAPPLICATION_DECLSPEC MenuBar : public QMenuBar
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

#endif // NOT XXPopulatedMenuBarH
