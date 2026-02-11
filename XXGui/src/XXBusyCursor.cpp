#include "XXBusyCursor.h"

#include <QCursor>
#include <QGuiApplication>

BusyCursor::BusyCursor()
{
   QGuiApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
   QGuiApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}

BusyCursor::~BusyCursor()
{
   QGuiApplication::restoreOverrideCursor();
}
