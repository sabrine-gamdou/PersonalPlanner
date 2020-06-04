#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QAbstractTableModel>
class TaskListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TaskListModel(QObject *parent = 0);

    void populateData(const QList<QString> &titleList, const QList<QString> &dateList, const QList<QString> &descriptionList, const QList<QString> &importanceList, const QList<QString> &repetitionList);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> m_titleList;
    QList<QString> m_dateList;
    QList<QString> m_descriptionList;
    QList<QString> m_importanceList;
    QList<QString> m_repetitionList;

};

#endif // TASKLISTMODEL_H
