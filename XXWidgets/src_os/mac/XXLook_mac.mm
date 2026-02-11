#include "XXLook.h"

#include <AppKit/NSApplication.h>
#include <AppKit/NSDockTile.h>
#include <AppKit/AppKit.h>

// see https://forum.qt.io/topic/109819/badgelable-related-methods-deprecated-how-to-access-nsapp-etc-from-qt/2


void Look::setDockLabel(const QString& label)
{
    [[NSApplication sharedApplication] dockTile].badgeLabel = label.toNSString();
}


void Look::updateDockIcon(const QIcon& icon)
{
    QPixmap pixmap = icon.pixmap(QSize(128, 128));
    NSImage *nsImage = [[NSImage alloc] initWithSize:NSMakeSize(pixmap.width(), pixmap.height())];
    [nsImage addRepresentation:[[NSBitmapImageRep alloc] initWithCGImage:pixmap.toImage().toCGImage()]];
    [NSApp setApplicationIconImage:nsImage];
    [[NSApp dockTile] display];
    [nsImage release];
}
