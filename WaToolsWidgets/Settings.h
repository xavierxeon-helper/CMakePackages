#ifndef SettingsH
#define SettingsH

#include "WaToolsWidgetsExportDef.h"
#include <FunctionCaller.h>
#include <QObject>

#include <RecentFiles.h>

class WATOOLSWIDGETS_DECLSPEC Settings : public Function::Caller<"Settings">
{
public:
   Settings();

public:
   class Admin;

public:
   static void reloadAll();
   static void modifiedAll(bool dirty);

protected:
   void initSettings(const QString& key, const QJsonValue& content);
   void setSettings(const QString& key, const QJsonValue& content);
   QJsonValue getSettings(const QString& key) const;

   virtual void reload();
   virtual void modified(bool dirty);

private:
   static QJsonObject data;
};

class WATOOLSWIDGETS_DECLSPEC Settings::Admin : public QObject
{
   Q_OBJECT

public:
   Admin(QWidget* mainWindow, const QString& fileDescription = "json");

public:
   void loadLastFile();
   void loadFile(const QString& fileName);

private:
   void newSettings();
   void loadSettings();
   void saveSettings();
   void saveAsSettings();

   void setFileName(const QString& newFileName);
   void loadInternal();
   void saveInternal() const;

private:
   QWidget* mainWindow;
   const QString fileDescription;
   RecentFiles recentFiles;
   QString fileName;
};

#endif // NOT SettingsH
