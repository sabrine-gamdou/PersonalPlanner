#include "statisticview.h"

QT_CHARTS_USE_NAMESPACE

StatisticView::StatisticView (QGraphicsItem *parent, Qt::WindowFlags wFlags)
: QChart(QChart::ChartTypeCartesian, parent, wFlags),
  p_currentModel(0),
  p_axisX(new QBarCategoryAxis()),
  p_axisY(new QValueAxis())
{
  addAxis(p_axisY, Qt::AlignLeft);
  addAxis(p_axisX, Qt::AlignBottom);
}


void StatisticView::changeSeries(StatisticModel *model){
    if (p_currentModel)
        removeSeries(p_currentModel);

    p_currentModel = model;

    // Reset axis
    p_axisX->setCategories(p_currentModel->categories());
    addSeries(model);
    model->attachAxis(p_axisX);
    model->attachAxis(p_axisY);
    p_axisY->setRange(0,p_currentModel->maxValue());
    setTitle(model->name());
}

//Slot
void StatisticView::handleClicked(int index, QBarSet *barset){
    Q_UNUSED(barset)
    StatisticModel *model = static_cast<StatisticModel *>(sender());
    changeSeries(model->statisticModel(index));
}
