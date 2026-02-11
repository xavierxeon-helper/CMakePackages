#ifndef XXRecentFilesHPP
#define XXRecentFilesHPP

#include "XXRecentFiles.h"

template <typename TargetClass>
void XX::RecentFiles::setup(TargetClass* instance, void (TargetClass::*memberFunction)(const QString&), int _maxEntries)
{
   loadFunction = std::bind(memberFunction, instance, std::placeholders::_1);
   maxEntries = _maxEntries;
}

#endif // NOT XXRecentFilesHPP