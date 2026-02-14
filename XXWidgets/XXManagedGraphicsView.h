#ifndef XXManagedGraphicsViewH
#define XXManagedGraphicsViewH

#include "XXWidgetsExportDef.h"
#include <QGraphicsView>

namespace XX
{
   namespace Managed
   {
      //! @brief managed QGraphicsView
      //! @details can manage events on its items
      //! @ingroup XXWidgets

      class XXWIDGETS_DECLSPEC GraphicsView : public QGraphicsView
      {
         Q_OBJECT

      public:
         GraphicsView(QWidget* parent);

      public:
         template <typename TargetClass>
         void onClicked(TargetClass* instance, bool (TargetClass::*memberFunction)(const QPointF&, QGraphicsItem*));

         void deactivateFrame();

      private:
         using ClickFunction = std::function<bool(const QPointF&, QGraphicsItem*)>;

      private:
         void mousePressEvent(QMouseEvent* event) override;

      private:
         ClickFunction mousePressFunction;
      };
   } // namespace Managed
} // namespace XX

#ifndef XXManagedGraphicsViewHPP
#include "XXManagedGraphicsView.hpp"
#endif // NOT XXManagedGraphicsViewHPP

#endif // NOT XXManagedGraphicsViewH
