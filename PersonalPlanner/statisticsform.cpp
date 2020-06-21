#include "statisticsform.h"
#include "ui_statisticsform.h"

StatisticsForm::StatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsForm)
{
    ui->setupUi(this);
}

StatisticsForm::~StatisticsForm()
{
    delete ui;
}


void StatisticsForm::createStructure(){

    monthModel = new StatisticModel(months, 100, view);
    monthModel->setName("Statistic of your Tasks from June - December");

    for (int month = 0; month < months.count(); month++) {
        weeklyModel = new StatisticModel (weeks, 50, view);
        monthModel->mapStatisticModel(month, weeklyModel);
        for ( int week = 0; week < weeks.count(); week++) {
            weeklyModel->mapStatisticModel(week, monthModel);
            weeklyModel->setName(QString("Task by week - " + months.at(month)));
        }

        QObject::connect(weeklyModel, &StatisticModel::clicked, view, &StatisticView::handleClicked);
    }
    QObject::connect(monthModel, &StatisticModel::clicked, view, &StatisticView::handleClicked);
}

void StatisticsForm::populateData() {
    for (const QString &state : status) {
        QBarSet *monthlyStatus = new QBarSet(state);
        for (int month = 0; month < months.count(); month++) {
            QBarSet *weeklyStatus = new QBarSet(state);
            for (int week = 0; week < weeks.count(); week++) {
                sortDateWeeks(month, week);
                for (int i = 0; i < 2; i++) {
                     *weeklyStatus << statusListStatistic.at(i);
                }

                // Get the drilldown series from season series and add crop to it.
            }
            monthModel->statisticModel(month)->append(weeklyStatus);
            *monthlyStatus << weeklyStatus->sum();
        }
        monthModel->append(monthlyStatus);
    }
}

void StatisticsForm::initializeData() {

    // Show season series in initial view
    view->changeSeries(monthModel);
    view->setTitle(monthModel->name());

    view->axes(Qt::Horizontal).first()->setGridLineVisible(false);
    view->legend()->setVisible(true);
    view->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(view);

}

void StatisticsForm::sortDateMonths(int month) {
    int completed = 0;
    int failed = 0;
    int inProgress = 0;
    int sum = 0;

    for (int week = 0; week < 4; week++) {
        sortDateWeeks(month, week);

        completed += statusListStatistic.at(0);
        failed += statusListStatistic.at(1);
        inProgress += statusListStatistic.at(2);
    }
    sum = completed + failed + inProgress;
}

void StatisticsForm::sortDateWeeks(int month, int week) {
    int completed = 0;
    int failed = 0;
    int inProgress = 0;

    for ( int i = 0; i < m_taskManager.getTaskList().length(); i++) {
        if (m_taskManager.getTaskList().at(i).date().month() == month) {
            for (int i = 0; i < 4; i++) {
                for (int j = 1; j < 8; j++) {
                    if ((m_taskManager.getTaskList().at(i).date().day() == (j+(7*i))) && (i+1 == week)){

                        if ( m_taskManager.getTaskList().at(i).status() == "Completed")
                            completed++;
                        else if ( m_taskManager.getTaskList().at(i).status() == "Failed")
                            failed++;
                        else if  ( m_taskManager.getTaskList().at(i).status() == "In-Progress")
                            inProgress++;
                    }
                }
            }
        }
    }
    statusListStatistic.append(completed);
    statusListStatistic.append(failed);
    statusListStatistic.append(inProgress);

   // combinedList.at(week-1).append(statusList);
}

StatisticView *StatisticsForm::getView() const
{
    return view;
}

void StatisticsForm::setUsername(const QString &value)
{
    username = value;
}

