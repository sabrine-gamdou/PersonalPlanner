#include "tasklistmodel.h"
#include <QDebug>
TaskListModel::TaskListModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void TaskListModel::populateData(const QList<Task>& taskList)
{
    m_taskList.clear();
    m_taskList = taskList;
}

int TaskListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_taskList.length();
}

int TaskListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

bool TaskListModel::removeRow(int position, int rows, const QModelIndex &parent) {
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
        m_taskList.removeAt(position);


    endRemoveRows();
    return true;
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.column() == 0) {
        return m_taskList[index.row()].title();
    } else if (index.column() == 1) {
        return m_taskList[index.row()].date();
    } else if (index.column() == 2) {
        return m_taskList[index.row()].description();
    } else if (index.column() == 3) {
        return m_taskList[index.row()].importance();
    } else if (index.column() == 4) {
        return m_taskList[index.row()].repetition();
    }


    return QVariant();
}

QVariant TaskListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Title");
        } else if (section == 1) {
            return QString("Date");
        }else if (section == 2) {
            return QString("Description");
        }else if (section == 3) {
            return QString("Importance");
        }else if (section == 4) {
            return QString("Repetition");
        }
    }
    return QVariant();
}

QList<Task> TaskListModel::taskList() const
{
    return m_taskList;
}

void TaskListModel::setTaskList(const QList<Task> &taskList)
{
    m_taskList = taskList;
}
