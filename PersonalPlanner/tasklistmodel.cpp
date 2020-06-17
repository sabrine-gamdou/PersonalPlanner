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
    return static_cast<int>(ColumnNames::Count);
}

bool TaskListModel::removeRow(int position, int rows, const QModelIndex &parent) {

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
        m_taskList.removeAt(position);

    endRemoveRows();

    return true;
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    switch(static_cast<ColumnNames>(index.column())){
    case ColumnNames::Title:
        return m_taskList[index.row()].title();
    case ColumnNames::Date:
        return m_taskList[index.row()].date();
    case ColumnNames::Description:
        return m_taskList[index.row()].description();
    case ColumnNames::Importance:
        return m_taskList[index.row()].importance();
    case ColumnNames::Repetition:
        return m_taskList[index.row()].repetition();
    case ColumnNames::Status:
       return m_taskList[index.row()].status();

    }

//    switch(role ) {
//    case Qt::BackgroundRole: {
//        if (m_taskList[index.row()].status() == "Completed")
//            return QBrush (QColor(50,205,50));

//        else if (m_taskList[index.row()].status() == "Failed")
//            return QBrush (QColor(255,0,0));

//        else if (m_taskList[index.row()].status() == "In-Progress")
//            return QBrush (QColor(255,215,0));
//    default:break;
//    }

//    }

    return QVariant();
}


QVariant TaskListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(static_cast<ColumnNames>(section)){
        case ColumnNames::Title:
            return QString("Title");
        case ColumnNames::Date:
            return QString("Date");
        case ColumnNames::Description:
            return QString("Description");
        case ColumnNames::Importance:
            return QString("Importance");
        case ColumnNames::Repetition:
            return QString("Repetition");
        case ColumnNames::Status:
            return QString("Status");
        default: break;
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
