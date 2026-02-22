#include "XXLoggerModel.h"

XX::LoggerModel::LoggerModel(QObject* parent, int stackSize)
   : QStandardItemModel(parent)
   , Logger::Target(stackSize)
{
}

void XX::LoggerModel::update(const Entry::Buffer& buffer)
{
   QStandardItemModel::clear();
   setHorizontalHeaderLabels({"TimeStamp", "Message"});

   static const QString timeFormat("yyyy-MM-dd hh:mm:ss");

   for (const Entry& entry : std::as_const(buffer))
   {
      auto createItem = [&](const QString text)
      {
         QStandardItem* item = new QStandardItem(text);
         item->setEditable(false);
         item->setForeground(QBrush(entry.color));

         return item;
      };

      const QString time = entry.timeStamp.toString(timeFormat);
      QStandardItem* timeItem = createItem(time);

      QStandardItem* textItem = createItem(entry.text);

      invisibleRootItem()->appendRow({timeItem, textItem});
   };

   emit contentUpdated();
}
