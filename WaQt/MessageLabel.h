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
   MessageLabel(QWidget* parent, int stackSize, bool showToolTip = true);

public:
   QTextDocument* getHistoryDocument();

private slots:
   void slotUpdateTimeout();

private:
   void print(const QString& text, bool isWarning) override;
   void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
   const int stackSize;
   const bool showToolTip;
   QStringList messageStack;
   QTextDocument historyDocument;
   QDateTime messageExpiration;
};

#endif // NOT MessageLabelH
