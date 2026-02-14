#ifndef XXMessageModelH
#define XXMessageModelH

#include "XXGuiExportDef.h"
#include <XXLogger.h>
#include <QStandardItemModel>

namespace XX
{
   //! @brief expose a logger as a QStandardItemModel
   //! @ingroup XXGui

   class XXGUI_DECLSPEC MessageModel : public QStandardItemModel, private Logger::Target
   {
      Q_OBJECT

   public:
      MessageModel(QObject* parent, int stackSize);

   signals:
      void contentUpdated();

   private:
      void update(const Entry::Buffer& buffer) override;
   };
} // namespace XX

#endif // NOT XXMessageModelH
