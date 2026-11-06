#ifndef XXDropLabelH
#define XXDropLabelH

#include "XXWidgetsExportDef.h"
#include <QLabel>

class QMimeData;

namespace XX
{
   class XXWIDGETS_DECLSPEC DropLabel : public QLabel
   {
      Q_OBJECT

   public:
      DropLabel(QWidget* parent);
      virtual ~DropLabel() override;

   public:
      template <typename TargetClass>
      void onDrop(TargetClass* instance, void (TargetClass::*memberFunction)(const QString&));

   private:
      using DropFunction = std::function<void(const QString&)>;

   private:
      void dropEvent(QDropEvent* de) override;
      void dragEnterEvent(QDragEnterEvent* dee) override;
      QString getFirstLocalFile(const QMimeData* mimeData) const;

   private:
      DropFunction dropFunction;
   };
} // namespace XX

#ifndef XXDropLabelHPP
#include "XXDropLabel.hpp"
#endif // NOT XXDropLabelHPP

#endif // NOT XXDropLabelH
