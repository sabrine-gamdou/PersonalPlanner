#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QtCharts/QStackedBarSeries>
#include <QtCore/QMap>

QT_CHARTS_USE_NAMESPACE


class StatisticModel : public QStackedBarSeries
{
    Q_OBJECT
public:
    StatisticModel(QStringList categories, int maxValue, QObject *parent = 0);

    void mapStatisticModel(int index, StatisticModel *statisticModel);
    StatisticModel *statisticModel(int index);
    QStringList categories();
    int maxValue();

private:
    QMap<int, StatisticModel *> m_statisticModel;
    QStringList m_categories;
    int m_maxValue;
};

#endif // STATISTICMODEL_H
