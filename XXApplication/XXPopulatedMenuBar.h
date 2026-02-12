#ifndef XXPopulatedMenuBarH
#define XXPopulatedMenuBarH

#include "XXApplicationExportDef.h"
#include <QMenuBar>

namespace XX
{
   namespace Populated
   {
      class XXAPPLICATION_DECLSPEC MenuBar : public QMenuBar
      {
         Q_OBJECT
         Q_PROPERTY(QString menuBarName READ getMenuBarName WRITE setMenuBarName NOTIFY menuBarNameChanged)

      public:
         explicit MenuBar(QWidget* parent = nullptr);

      signals:
         void menuBarNameChanged();

      public:
         const QString& getMenuBarName() const;
         void setMenuBarName(const QString& name);
         void init();

      private:
         QString menuBarName;
      };
   } // namespace Populated
} // namespace XX

#endif // NOT XXPopulatedMenuBarH
