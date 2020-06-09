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

    QList<QString> titleList() const;
    void setTitleList(const QList<QString> &titleList);

    QList<QString> dateList() const;
    void setDateList(const QList<QString> &dateList);

    QList<QString> descriptionList() const;
    void setDescriptionList(const QList<QString> &descriptionList);

    QList<QString> importanceList() const;
    void setImportanceList(const QList<QString> &importanceList);

    QList<QString> repetitionList() const;
    void setRepetitionList(const QList<QString> &repetitionList);

private:
    QList<QString> m_titleList;
    QList<QString> m_dateList;
    QList<QString> m_descriptionList;
    QList<QString> m_importanceList;
    QList<QString> m_repetitionList;

};

#endif // TASKLISTMODEL_H
