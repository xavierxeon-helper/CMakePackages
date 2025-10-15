#include "Settings.h"

#include <QFileDialog>
#include <QSettings>

#include <FileTools.h>
#include <Logger.h>

// admin

Settings::Admin::Admin(QWidget* mainWindow, const QString& fileDescription)
   : QObject(mainWindow)
   , mainWindow(mainWindow)
   , fileDescription(fileDescription)
   , recentFiles(mainWindow, "RecentFiles", "Settings.Recent")
   , fileName()
{
   auto addAction = [&](QIcon icon, QString text, QString objectName, auto slotFunction) -> QAction*
   {
      QAction* action = new QAction(icon, text, mainWindow);
      action->setObjectName(objectName);
      connect(action, &QAction::triggered, this, slotFunction);

      return action;
   };

   addAction(QIcon(":/New.svg"), "New", "Settings.New", &Admin::newSettings);
   QAction* loadAction = addAction(QIcon(":/Load.svg"), "Load", "Settings.Load", &Admin::loadSettings);
   QAction* saveAction = addAction(QIcon(":/Save.svg"), "Save", "Settings.Save", &Admin::saveSettings);
   QAction* saveAsAction = addAction(QIcon(":/SaveAs.svg"), "Save As", "Settings.SaveAs", &Admin::saveAsSettings);

   loadAction->setShortcut(QKeySequence::Open);
   saveAction->setShortcut(QKeySequence::Save);
   saveAsAction->setShortcut(QKeySequence::SaveAs);

   RecentFiles::LoadFunction loadFunction = std::bind(&Admin::loadFile, this, std::placeholders::_1);
   recentFiles.setup(loadFunction, 10);
}

void Settings::Admin::loadLastFile()
{
   QSettings settings;

   const QString fileName = settings.value("LastFile").toString();
   loadFile(fileName);
}

void Settings::Admin::loadFile(const QString& fileName)
{
   if (fileName.isEmpty() || !QFile::exists(fileName))
      return;

   setFileName(fileName);
   loadInternal();
}

void Settings::Admin::newSettings()
{
   const QString fileName = QFileDialog::getSaveFileName(mainWindow, "New Project Settings", QString(), fileDescription);
   if (fileName.isEmpty())
      return;

   setFileName(fileName);
   saveInternal();

   loadInternal();

   Settings::modifiedAll(false);
}

void Settings::Admin::loadSettings()
{
   const QString fileName = QFileDialog::getOpenFileName(mainWindow, "Load Project Settings", QString(), fileDescription);
   if (fileName.isEmpty())
   {
      qDebug() << __FUNCTION__ << "No file selected";
      return;
   }

   setFileName(fileName);
   loadInternal();

   Settings::modifiedAll(false);
}

void Settings::Admin::saveSettings()
{
   if (fileName.isEmpty())
      return saveAsSettings();

   saveInternal();

   Settings::modifiedAll(false);
}

void Settings::Admin::saveAsSettings()
{
   const QString fileName = QFileDialog::getSaveFileName(mainWindow, "Save Project Settings", QString(), fileDescription);
   if (fileName.isEmpty())
      return;

   setFileName(fileName);
   saveInternal();

   Settings::modifiedAll(false);
}

void Settings::Admin::setFileName(const QString& newFileName)
{
   if (!newFileName.endsWith(".voc"))
      fileName = newFileName + ".voc";
   else
      fileName = newFileName;

   recentFiles.add(fileName);

   QFileInfo info(fileName);
   mainWindow->setWindowTitle("VoiceGenerator - " + info.fileName() + " [*]");

   QSettings settings;
   settings.setValue("LastFile", fileName);
}

void Settings::Admin::loadInternal()
{
   using MergeFunction = std::function<void(const QJsonObject&, QJsonObject&)>;
   MergeFunction mergeObject = [&](const QJsonObject& source, QJsonObject& target)
   {
      for (QJsonObject::const_iterator it = source.constBegin(); it != source.constEnd(); ++it)
      {
         const QString& key = it.key();
         if ("settings" == key)
         {
            target[key] = it.value();
         }
         else
         {
            if (!target.contains(key))
            {
               qWarning() << __FUNCTION__ << "Key not found in target:" << key;
               continue;
            }

            if (!it.value().isObject())
            {
               target[key] = it.value();
            }
            else
            {
               QJsonObject sourceObject = it.value().toObject();
               QJsonObject targetObject = target[key].toObject();

               mergeObject(sourceObject, targetObject);
               target[key] = targetObject;
            }
         }
      }
   };

   const QJsonObject loadData = FileTools::readJson(fileName);
   mergeObject(loadData, Settings::data);

   Logger::stream() << "Project settings loaded from" << fileName;

   QSettings settings;
   settings.setValue("LastFile", fileName);

   Settings::reloadAll();
}

void Settings::Admin::saveInternal() const
{
   FileTools::writeJson(Settings::data, fileName);

   QSettings settings;
   settings.setValue("LastFile", fileName);
}

// settings

QJsonObject Settings::data;

Settings::Settings()
   : Function::Caller<"Settings">()
{
}

void Settings::reloadAll()
{
   callOnAll(&Settings::reload);
}

void Settings::modifiedAll(bool dirty)
{
   callOnAll(&Settings::modified, dirty);
}

void Settings::initSettings(const QString& key, const QJsonValue& content)
{
   data[key] = content;
}

void Settings::setSettings(const QString& key, const QJsonValue& content)
{
   data[key] = content;
}

QJsonValue Settings::getSettings(const QString& key) const
{
   return data[key];
}

void Settings::reload()
{
   // do nothing
}

void Settings::modified(bool dirty)
{
   // do nothing
}
