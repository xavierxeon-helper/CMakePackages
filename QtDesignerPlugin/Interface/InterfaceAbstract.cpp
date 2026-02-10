#include "InterfaceAbstract.h"

#include <QFile>

Interface::Abstract::Abstract(QObject* parent)
   : QObject(parent)
{
}

void Interface::Abstract::initialize(QDesignerFormEditorInterface* /* core */)
{
   if (initialized)
      return;

   initialized = true;
}

bool Interface::Abstract::isInitialized() const
{
   return initialized;
}

bool Interface::Abstract::isContainer() const
{
   return false;
}

QIcon Interface::Abstract::icon() const
{
   return QIcon();
}

QString Interface::Abstract::toolTip() const
{
   return QString();
}

QString Interface::Abstract::whatsThis() const
{
   return QString();
}

QString Interface::Abstract::group() const
{
   return QString("WaTools Widgets");
}

QString Interface::Abstract::readFile(const QString& fileName) const
{
   QFile file(fileName);
   if (!file.open(QIODevice::ReadOnly))
      return QString();

   const QString text = file.readAll();
   file.close();

   return text;
}
