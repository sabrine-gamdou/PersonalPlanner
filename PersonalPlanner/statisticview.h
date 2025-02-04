#ifndef STATISTICVIEW_H
#define STATISTICVIEW_H

#include "statisticmodel.h"

#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>

namespace QtCharts {
class QBarCategoryAxis;
class QValueAxis;
}

QT_CHARTS_USE_NAMESPACE

class StatisticView : public QChart
{
    Q_OBJECT
public:
    explicit StatisticView(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});

    void changeSeries(StatisticModel *model);

public slots:
    void handleClicked(int index, QBarSet *barset);

private:
    StatisticModel *p_currentModel;
    QBarCategoryAxis *p_axisX;
    QValueAxis *p_axisY;

};

#endif // STATISTICVIEW_H





