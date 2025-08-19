#ifndef MessageModelH
#define MessageModelH

#include "WaToolsQtExportDef.h"
#include <Logger.h>
#include <QStandardItemModel>

class WATOOLS_QT_DECLSPEC MessageModel : public QStandardItemModel, private Logger::Target
{
   Q_OBJECT

public:
   MessageModel(QObject* parent, int stackSize);

signals:
   void contentUpdated();

private:
   void update(const Entry::Buffer& buffer) override;
};

#endif // NOT MessageModelH
