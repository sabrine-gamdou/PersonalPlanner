#include "statisticsform.h"
#include "ui_statisticsform.h"

StatisticsForm::StatisticsForm(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::StatisticsForm)
{

    ui->setupUi(this);
}

StatisticsForm::~StatisticsForm()
{
    delete ui;
}


void StatisticsForm::createStructure(){


    monthModel->setName("Statistic of your Task Status from June - December");

    for (int month = 0; month < months.count(); month++) {
        weeklyModel = new StatisticModel (weeks, 50, view);
        monthModel->mapStatisticModel(month, weeklyModel);
        for ( int week = 0; week < weeks.count(); week++) {
            weeklyModel->mapStatisticModel(week, monthModel);
            weeklyModel->setName(QString("Status by week - " + months.at(month)));
        }

        QObject::connect(weeklyModel, &StatisticModel::clicked, view, &StatisticView::handleClicked);
    }
    QObject::connect(monthModel, &StatisticModel::clicked, view, &StatisticView::handleClicked);
}

void StatisticsForm::populateData() {
    QMap<int, QList<QList<int>>>::const_iterator month;
    for (const QString &state : status) {
        QBarSet *monthlyStatus = new QBarSet(state);
        for (month = monthlyMap.begin(); month != monthlyMap.end(); ++month) {
            QBarSet *weeklyStatus = new QBarSet(state);
            for (int week = 0; week < weeks.count(); week++) {
                for (int i = 0; i < 2; i++) {
                    //qDebug() << month.value().at(week).at(i);
                   // *weeklyStatus << month.value().at(week).at(i);
                }
            }
            //++month;
          //  monthModel->statisticModel(month.key())->append(weeklyStatus);
            *monthlyStatus << weeklyStatus->sum();
        }
        monthModel->append(monthlyStatus);
    }
}


void StatisticsForm::initializeData() {
    view = new StatisticView();
    monthModel = new StatisticModel(months, 10, view);
    initializeMap();
    createStructure();
    populateData();


    // Show season series in initial view
    view->changeSeries(monthModel);
    view->setTitle(monthModel->name());

    view->axes(Qt::Horizontal).first()->setGridLineVisible(false);
    view->legend()->setVisible(true);
    view->legend()->setAlignment(Qt::AlignBottom);
    //  ui->set
    QChartView *chartView = new QChartView(view);
    setCentralWidget(chartView);
    resize(480,300);
    show();

}

void StatisticsForm::initializeMap(){
    for (int month = 0; month < months.count(); ++month) {
        for (int week = 0; week < weeks.count(); week++) {
            sortDateWeeks2(month,week);
        }
    }
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
                    if ((m_taskManager.getTaskList().at(i).date().day() == (j+(7*i))) && ((i+1) == week)){

                        if ( m_taskManager.getTaskList().at(i).status() == "Completed")
                            completed++;
                        else if ( m_taskManager.getTaskList().at(i).status() == "Failed")
                            failed++;
                        else if  ( m_taskManager.getTaskList().at(i).status() == "In-Progress")
                            inProgress++;
                    }

                }
                statusListStatistic.append(completed);
                statusListStatistic.append(failed);
                statusListStatistic.append(inProgress);
            }
        }
    }


    // combinedList.at(week-1).append(statusList);
}

void StatisticsForm::sortDateWeeks2(int month, int week) {
    int completed = 0;
    int failed = 0;
    int inProgress = 0;
    qDebug() << tasksList.length();
    for ( int i = 0; i < tasksList.length(); i++) {
        qDebug() << "Month: " << month+6;
       // if (tasksList.at(i).date().month() == (month+6)) { // because we start at June(6) till December(12)
            // for (int i = 0; i < 4; i++) { // go through each week
            for (int j = 1; j < 8; j++) { // go through each day of chosen week of month
                qDebug() << "Day: "<< tasksList.at(i).date().day();
                if ((tasksList.at(i).date().day() == (j+(7*week))) && (tasksList.at(i).date().month() == (month+6))){ // go through all 31 days
                    if ( tasksList.at(i).status() == "Completed")
                      qDebug() <<  completed++;
                    else if ( tasksList.at(i).status() == "Failed")
                       qDebug() << failed++;
                    else if  ( tasksList.at(i).status() == "In-Progress")
                       qDebug() << inProgress++;
                }

                // }
                QList<int> statusList;
                QList<QList<int>> combinedMonths;
                statusList.append(completed);
                statusList.append(failed);
                statusList.append(inProgress);
                combinedMonths.append(statusList);
            }
            //map the List of Weeks(in itself it is also a List of integer or the status counters) to each month
            monthlyMap.insert(month,combinedList);
        }
   // }
}

QList<Task> StatisticsForm::getTasksList() const
{
    return tasksList;
}

void StatisticsForm::setTasksList(const QList<Task> &value)
{
    tasksList = value;
}

StatisticView *StatisticsForm::getView() const
{
    return view;
}

void StatisticsForm::setUsername(const QString &value)
{
    username = value;
}

