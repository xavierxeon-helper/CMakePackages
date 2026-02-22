#ifndef XXLoggerLabelH
#define XXLoggerLabelH

#include "XXWidgetsExportDef.h"
#include <XXLogger.h>
#include <QLabel>

#include <QDateTime>

namespace XX
{

   //! @brief a QLabel that can display log messages
   //! @details can display log messages from a Logger
   //! @ingroup XXWidgets

   class XXWIDGETS_DECLSPEC LoggerLabel : public QLabel, public Logger::Target
   {
      Q_OBJECT

   public:
      LoggerLabel(QWidget* parent, int stackSize = 10);

   public:
      void setShowToolTip(bool newShowToolTip);

   private slots:
      void slotUpdateTimeout();

   private:
      void update(const Entry::Buffer& buffer) override;
      void mouseDoubleClickEvent(QMouseEvent* event) override;

   private:
      bool showToolTip;
      QDateTime messageExpiration;
   };
} // namespace XX

#endif // NOT XXLoggerLabelH
