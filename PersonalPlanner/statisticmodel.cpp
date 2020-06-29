#include "statisticmodel.h"

QT_CHARTS_USE_NAMESPACE

StatisticModel::StatisticModel(QStringList categories, int maxValue, QObject *parent)
    : QStackedBarSeries(parent),m_maxValue(maxValue)
{
    m_categories = categories;
}


void StatisticModel::mapStatisticModel(int index, StatisticModel *statisticModel){
    m_statisticModel[index] = statisticModel;
}


StatisticModel *StatisticModel::statisticModel(int index){
    return m_statisticModel[index];
}


QStringList StatisticModel::categories(){
    return m_categories;
}


int StatisticModel::maxValue(){
    return m_maxValue;
}
