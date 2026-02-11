#include "XXTabStackModel.h"

#include "XXTabStackWidget.h"

XX::TabStack::Model::Model(QObject* parent)
   : QStandardItemModel(parent)
   , maxRows(0)
   , maxDepth(0)
   , labelMatrix()
{
}

void XX::TabStack::Model::init(Widget* tabStack)
{
   QStringList allLabels = tabStack->getAllTabLabels();
   maxRows = allLabels.size();
   maxDepth = tabStack->depthCount();

   labelMatrix.resize(maxDepth, QStringList());

   setRowCount(maxRows);
   setColumnCount(maxDepth);

   // headers
   for (int depth = 0; depth < maxDepth; depth++)
   {
      const QString headerText = QString("Depth %1").arg(depth + 1);
      QStandardItem* headerItem = new QStandardItem(headerText);
      headerItem->setData(headerText, RoleName);

      setHorizontalHeaderItem(depth, headerItem);
   }

   // items
   for (int depth = 0; depth < maxDepth; depth++)
   {
      const QStringList depthLabels = tabStack->getTabOrder(depth);

      for (int row = 0; row < maxRows; row++)
      {
         const QString& label = row < depthLabels.size() ? depthLabels.at(row) : "";
         QStandardItem* tabItem = new QStandardItem();
         tabItem->setData("", RoleName);

         setItem(row, depth, tabItem);

         allLabels.removeAll(label);
         if (!label.isEmpty())
            labelMatrix[depth].append(label);
      }
   }

   if (!allLabels.isEmpty())
   {
      qWarning() << "orpahned tabs" << allLabels;
   }

   updateLabels();
}

void XX::TabStack::Model::apply(Widget* tabStack)
{
   for (int depth = 0; depth < maxDepth; depth++)
   {
      const QStringList& labels = labelMatrix[depth];
      tabStack->setTabOrder(depth, labels);
   }

   tabStack->setActiveDepth(0);
}

void XX::TabStack::Model::reOrder(int sourceRow, int sourceColumn, int targetRow, int targetColumn)
{
   QStringList& sourceLabels = labelMatrix[sourceColumn];
   QStringList& targetLabels = labelMatrix[targetColumn];

   const QString sourceName = sourceLabels.at(sourceRow);
   if (sourceName.isEmpty()) // nothing to move
      return updateLabels();

   sourceLabels.removeAll(sourceName);

   if (targetRow >= targetLabels.size())
      targetLabels.append(sourceName);
   else
      targetLabels.insert(targetRow, sourceName);

   updateLabels();
}

void XX::TabStack::Model::updateLabels()
{
   beginResetModel();

   for (int depth = 0; depth < maxDepth; depth++)
   {
      const QStringList& labels = labelMatrix[depth];
      for (int row = 0; row < maxRows; row++)
      {
         const QString text = row < labels.size() ? labels.at(row) : "";

         QStandardItem* tabItem = item(row, depth);
         tabItem->setText(text);
         tabItem->setData(text, RoleName);
      }
   }
   endResetModel();
}

QHash<int, QByteArray> XX::TabStack::Model::roleNames() const
{
   QHash<int, QByteArray> data;
   data[RoleName] = "name";

   return data;
}
