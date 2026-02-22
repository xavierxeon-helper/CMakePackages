#ifndef XXLoggerModelH
#define XXLoggerModelH

#include "XXGuiExportDef.h"
#include <XXLogger.h>
#include <QStandardItemModel>

namespace XX
{
   //! @brief expose a logger as a QStandardItemModel
   //! @ingroup XXGui

   class XXGUI_DECLSPEC LoggerModel : public QStandardItemModel, private Logger::Target
   {
      Q_OBJECT

   public:
      LoggerModel(QObject* parent, int stackSize);

   signals:
      void contentUpdated();

   private:
      void update(const Entry::Buffer& buffer) override;
   };
} // namespace XX

#endif // NOT XXLoggerModelH
