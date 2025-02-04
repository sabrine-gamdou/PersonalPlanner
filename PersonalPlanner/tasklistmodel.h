#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include "task.h"

#include <QAbstractTableModel>
#include <QBrush>

class TaskListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TaskListModel(QObject *parent = 0);

    enum class ColumnNames{Title, Date, Description, Importance, Repetition, Status, Count};

    void populateData(const QList<Task> &taskList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    bool removeRow(int position, int rows);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QList<Task> taskList() const;
    void setTaskList(const QList<Task> &taskList);

private:
    QList<Task> m_taskList;
};

#endif // TASKLISTMODEL_H
