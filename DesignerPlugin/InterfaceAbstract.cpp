#include "InterfaceAbstract.h"

#include <QFile>

InterfaceAbstract::InterfaceAbstract(QObject* parent)
   : QObject(parent)
{
}

void InterfaceAbstract::initialize(QDesignerFormEditorInterface* /* core */)
{
   if (initialized)
      return;

   initialized = true;
}

bool InterfaceAbstract::isInitialized() const
{
   return initialized;
}

bool InterfaceAbstract::isContainer() const
{
   return false;
}

QIcon InterfaceAbstract::icon() const
{
   return QIcon();
}

QString InterfaceAbstract::toolTip() const
{
   return QString();
}

QString InterfaceAbstract::whatsThis() const
{
   return QString();
}

QString InterfaceAbstract::group() const
{
   return QString("Custom Widgets");
}

QString InterfaceAbstract::readFile(const QString& fileName) const
{
   QFile file(fileName);
   if (!file.open(QIODevice::ReadOnly))
      return QString();

   const QString text = file.readAll();
   file.close();

   return text;
}
