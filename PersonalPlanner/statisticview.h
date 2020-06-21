#ifndef STATISTICVIEW_H
#define STATISTICVIEW_H

#include <QtCharts/QChart>
#include "statisticmodel.h"

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

    void changeSeries(StatisticModel model);


public Q_SLOTS:
    void handleClicked(int index, QBarSet *barset);

private:
    StatisticModel m_currentModel;
    QBarCategoryAxis *m_axisX;
    QValueAxis *m_axisY;

};

#endif // STATISTICVIEW_H




