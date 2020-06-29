#include "statisticview.h"

QT_CHARTS_USE_NAMESPACE

StatisticView::StatisticView (QGraphicsItem *parent, Qt::WindowFlags wFlags)
: QChart(QChart::ChartTypeCartesian, parent, wFlags),
  m_currentModel(0),
  m_axisX(new QBarCategoryAxis()),
  m_axisY(new QValueAxis())
{
  addAxis(m_axisY, Qt::AlignLeft);
  addAxis(m_axisX, Qt::AlignBottom);
}

void StatisticView::changeSeries(StatisticModel *model){
    if (m_currentModel)
        removeSeries(m_currentModel);

    m_currentModel = model;

    // Reset axis
    m_axisX->setCategories(m_currentModel->categories());
    addSeries(model);
    model->attachAxis(m_axisX);
    model->attachAxis(m_axisY);
    m_axisY->setRange(0,m_currentModel->maxValue());
    setTitle(model->name());
}

//Slot
void StatisticView::handleClicked(int index, QBarSet *barset){
    Q_UNUSED(barset)
    StatisticModel *model = static_cast<StatisticModel *>(sender());
    changeSeries(model->statisticModel(index));
}
