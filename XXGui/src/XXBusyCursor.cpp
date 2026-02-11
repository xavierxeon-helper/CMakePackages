#include "XXBusyCursor.h"

#include <QCursor>
#include <QGuiApplication>

XX::BusyCursor::BusyCursor()
{
   QGuiApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
   QGuiApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}

XX::BusyCursor::~BusyCursor()
{
   QGuiApplication::restoreOverrideCursor();
}
