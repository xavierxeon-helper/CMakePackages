#ifndef DockToolsH
#define DockToolsH

#include <QIcon>
#include <QString>

class DockTools
{
public:
   static void showLabel(const QString& label);
   static void updateDockIcon(const QIcon& icon);
};

#endif // NOT DockToolsH
