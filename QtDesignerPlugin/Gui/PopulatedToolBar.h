#ifndef PopulatedToolBarH
#define PopulatedToolBarH

#include <QToolBar>

namespace Populated
{
   class ToolBar : public QToolBar
   {
      Q_OBJECT

      Q_PROPERTY(QString toolBarName READ getToolBarName WRITE setToolBarName NOTIFY toolBarNameChanged)

   public:
      explicit ToolBar(QWidget* parent = nullptr);

   signals:
      void toolBarNameChanged();

   private:
      const QString& getToolBarName() const;
      void setToolBarName(const QString& name);

   private:
      QString toolBarName;
   };
} // namespace Populated

#endif // NOT PopulatedToolBarH
