#ifndef XXTabStackModelH
#define XXTabStackModelH

#include "XXWidgetsExportDef.h"
#include <QStandardItemModel>

namespace XX
{
   namespace TabStack
   {
      class Widget;

      class XXWIDGETS_DECLSPEC Model : public QStandardItemModel
      {
         Q_OBJECT

      public:
         Model(QObject* parent);

      private:
         enum Roles
         {
            RoleName = Qt::UserRole + 1
         };

      public:
         void init(Widget* tabStack);
         void apply(Widget* tabStack);
         Q_INVOKABLE void reOrder(int sourceRow, int sourceColumn, int targetRow, int targetColumn);

      private:
         void updateLabels();
         QHash<int, QByteArray> roleNames() const override;

      private:
         int maxRows;
         int maxDepth;
         QList<QStringList> labelMatrix;
      };
   } // namespace TabStack
} // namespace XX

#endif // NOT XXTabStackModelH
