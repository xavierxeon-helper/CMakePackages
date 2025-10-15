#include "ProjectSettings.h"

#include <QFileDialog>
#include <QSettings>

#include <FileTools.h>
#include <Logger.h>

// admin

ProjectSettings::Admin::Admin(QWidget* mainWindow, const QString& fileDescription)
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

void ProjectSettings::Admin::loadLastFile()
{
   QSettings settings;

   const QString fileName = settings.value("LastFile").toString();
   loadFile(fileName);
}

void ProjectSettings::Admin::loadFile(const QString& fileName)
{
   if (fileName.isEmpty() || !QFile::exists(fileName))
      return;

   setFileName(fileName);
   loadInternal();
}

void ProjectSettings::Admin::newSettings()
{
   const QString fileName = QFileDialog::getSaveFileName(mainWindow, "New Project Settings", QString(), fileDescription);
   if (fileName.isEmpty())
      return;

   setFileName(fileName);
   saveInternal();

   loadInternal();

   ProjectSettings::modifiedAll(false);
}

void ProjectSettings::Admin::loadSettings()
{
   const QString fileName = QFileDialog::getOpenFileName(mainWindow, "Load Project Settings", QString(), fileDescription);
   if (fileName.isEmpty())
   {
      qDebug() << __FUNCTION__ << "No file selected";
      return;
   }

   setFileName(fileName);
   loadInternal();

   ProjectSettings::modifiedAll(false);
}

void ProjectSettings::Admin::saveSettings()
{
   if (fileName.isEmpty())
      return saveAsSettings();

   saveInternal();

   ProjectSettings::modifiedAll(false);
}

void ProjectSettings::Admin::saveAsSettings()
{
   const QString fileName = QFileDialog::getSaveFileName(mainWindow, "Save Project Settings", QString(), fileDescription);
   if (fileName.isEmpty())
      return;

   setFileName(fileName);
   saveInternal();

   ProjectSettings::modifiedAll(false);
}

void ProjectSettings::Admin::setFileName(const QString& newFileName)
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

void ProjectSettings::Admin::loadInternal()
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
   mergeObject(loadData, ProjectSettings::data);

   Logger::stream() << "Project settings loaded from" << fileName;

   QSettings settings;
   settings.setValue("LastFile", fileName);

   ProjectSettings::reloadAll();
}

void ProjectSettings::Admin::saveInternal() const
{
   FileTools::writeJson(ProjectSettings::data, fileName);

   QSettings settings;
   settings.setValue("LastFile", fileName);
}

// settings

QJsonObject ProjectSettings::data;

ProjectSettings::ProjectSettings()
   : Function::Caller<"Settings">()
{
}

void ProjectSettings::reloadAll()
{
   callOnAll(&ProjectSettings::reload);
}

void ProjectSettings::modifiedAll(bool dirty)
{
   callOnAll(&ProjectSettings::modified, dirty);
}

void ProjectSettings::initSettings(const QString& key, const QJsonValue& content)
{
   data[key] = content;
}

void ProjectSettings::setSettings(const QString& key, const QJsonValue& content)
{
   data[key] = content;
}

QJsonValue ProjectSettings::getSettings(const QString& key)
{
   return data[key];
}

void ProjectSettings::reload()
{
   // do nothing
}

void ProjectSettings::modified(bool dirty)
{
   // do nothing
}
