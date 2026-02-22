#ifndef XXQtMessageModelH
#define XXQtMessageModelH

#include "XXLogExportDef.h"
#include <QStandardItemModel>

namespace XX
{
   namespace QtMessage
   {
      //! @brief qt message as model
      //! @ingroup XXLog

      class XXLOG_DECLSPEC Model : public QStandardItemModel
      {
         Q_OBJECT

      public:
         Model(QObject* parent, int maxLines = -1);
         ~Model();

      private:
         enum Roles
         {
            RoleText = Qt::UserRole + 1,
            RoleIcon
         };

      private:
         void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

      private:
         const int maxLines;
      };
   } // namespace QtMessage
} // namespace XX

#endif // NOT XXQtMessageModelH
