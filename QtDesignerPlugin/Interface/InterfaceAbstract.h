#ifndef InterfaceAbstractH
#define InterfaceAbstractH

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

namespace Interface
{
   class Abstract : public QObject, public QDesignerCustomWidgetInterface
   {
      Q_OBJECT

   public:
      explicit Abstract(QObject* parent);

   public:
      void initialize(QDesignerFormEditorInterface* core) override;
      bool isInitialized() const override;

      bool isContainer() const override;
      QIcon icon() const override;
      QString toolTip() const override;
      QString whatsThis() const override;

      virtual QString group() const override;

   protected:
      QString readFile(const QString& fileName) const;

   private:
      bool initialized = false;
   };
} // namespace Interface

#endif // NOT InterfaceAbstractH
