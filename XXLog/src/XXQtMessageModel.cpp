#include "XXQtMessageModel.h"

#include "XXQtMessageInterceptor.h"

XX::QtMessage::Model::Model(QObject* parent, int maxLines)
   : QStandardItemModel(parent)
   , maxLines(maxLines)
{
   Interceptor::enable(this, &Model::outputMessage);

   QHash<int, QByteArray> roleNames;
   roleNames[RoleText] = "text";
   roleNames[RoleIcon] = "icon";
   setItemRoleNames(roleNames);
}

XX::QtMessage::Model::~Model()
{
   Interceptor::disable(this);
}

void XX::QtMessage::Model::outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   const QString icon = Interceptor::symbol(type);
   const QString text = icon + " " + msg;

   QStandardItem* item = new QStandardItem(text);
   item->setEditable(false);

   item->setData(msg, RoleText);
   item->setData(icon, RoleIcon);
   //item->setForeground(Document::messageColor(type));

   appendRow(item);
   if (maxLines > 0 && rowCount() > maxLines)
      removeRow(0);
}
