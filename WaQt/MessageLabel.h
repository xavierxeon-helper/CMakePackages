#ifndef MessageLabelH
#define MessageLabelH

#include "Logger.h"
#include <QLabel>

#include <QDateTime>
#include <QTextDocument>

class MessageLabel : public QLabel, public Logger
{
   Q_OBJECT

public:
   MessageLabel(QWidget* parent, int stackSize);

public:
   QTextDocument* getHistoryDocument();

   void setStackSize(const int& newStackSize);
   void clearStack();
   void setShowToolTip(bool newShowToolTip);
   void setAddTimeStamp(bool newAddTimeStamp);

private:
   struct Message
   {
      QDateTime timeStamp;
      QString symbol;
      QString text;

      using List = QList<Message>;
   };

private slots:
   void slotUpdateTimeout();
   void updateStack();

private:
   void print(const QString& text, bool isWarning) override;
   void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
   int stackSize;
   bool showToolTip;
   bool addTimeStamp;
   Message::List messageStack;
   QTextDocument historyDocument;
   QDateTime messageExpiration;
};

#endif // NOT MessageLabelH
