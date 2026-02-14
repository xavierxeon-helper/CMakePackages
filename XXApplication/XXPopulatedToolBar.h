#ifndef XXPopulatedToolBarH
#define XXPopulatedToolBarH

#include "XXApplicationExportDef.h"
#include <QToolBar>

namespace XX
{
   namespace Populated
   {
      //! @brief tool bar that can be populated with menu items based on XML resources
      //! @ingroup XXApplication

      class XXAPPLICATION_DECLSPEC ToolBar : public QToolBar
      {
         Q_OBJECT
         Q_PROPERTY(QString toolBarName READ getToolBarName WRITE setToolBarName NOTIFY toolBarNameChanged)

      public:
         explicit ToolBar(QWidget* parent = nullptr);

      signals:
         void toolBarNameChanged();

      public:
         const QString& getToolBarName() const;
         void setToolBarName(const QString& name);
         void init();

      private:
         QString toolBarName;
      };
   } // namespace Populated
} // namespace XX

#endif // NOT XXPopulatedToolBarH
