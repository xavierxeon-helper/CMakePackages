#ifndef MessageModelH
#define MessageModelH

#include <Logger.h>
#include <QStandardItemModel>

class MessageModel : public QStandardItemModel, private Logger::Target
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
