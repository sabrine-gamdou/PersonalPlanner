#include "tasklistmodel.h"

TaskListModel::TaskListModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void TaskListModel::populateData(const QList<QString> &titleList, const QList<QString> &dateList, const QList<QString> &descriptionList, const QList<QString> &importanceList, const QList<QString> &repetitionList)
{
    m_titleList.clear();
    m_titleList = titleList;

    m_dateList.clear();
    m_dateList = dateList;

    m_descriptionList.clear();
    m_descriptionList = descriptionList;

    m_importanceList.clear();
    m_importanceList = importanceList;

    m_repetitionList.clear();
    m_repetitionList = repetitionList;

    return;
}

int TaskListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_titleList.length();
}

int TaskListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return m_titleList[index.row()];
    } else if (index.column() == 1) {
        return m_dateList[index.row()];
    } else if (index.column() == 2) {
        return m_descriptionList[index.row()];
    } else if (index.column() == 3) {
        return m_importanceList[index.row()];
    } else if (index.column() == 4) {
        return m_repetitionList[index.row()];
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
