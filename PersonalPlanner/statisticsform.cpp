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
        weeklyModel = new StatisticModel (weeks, 10, view);
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
        int monthC = 0;
        for (month = monthlyMap.begin();month != monthlyMap.end();++month) {
            QBarSet *weeklyStatus = new QBarSet(state);
            for (int week = 0; week < weeks.count(); ++week) {
                qDebug() << "Map Keys list length: "<<monthlyMap.keys().length();
                qDebug() << "Week List length: " << month.value().length();
                qDebug() << "Status List length: " << month.value().at(week).length();
                qDebug() << "Month: "<< month.key()+6 << " Week: "<< week << "StatusType: "<< statusToInt(state)<< " Status: "<<month.value().at(week).at(statusToInt(state));
                *weeklyStatus <<  month.value().at(week).at(statusToInt(state));
            }
            ++monthC;
            monthModel->statisticModel(month.key())->append(weeklyStatus);
            *monthlyStatus << weeklyStatus->sum();
        }
        monthModel->append(monthlyStatus);
    }

}

int StatisticsForm::statusToInt(QString status){
    if(status == "Completed"){
        return 0;
    }else if(status == "Failed"){
        return 1;
    }else if(status == "In-Progress"){
        return 2;
    }
    return -1;
}

void StatisticsForm::initializeChart() {
    view = new StatisticView();
    monthModel = new StatisticModel(months, 40, view);
    sortDateWeeks();
    printMap();
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
    resize(600,400);
    show();

}


void StatisticsForm::sortDateWeeks() {
    qDebug() <<"Status: " <<status;
    for(int month = 0; month < months.length(); ++month){
        QList<QList<int>> combinedMonths;
        for(int week = 0; week < weeks.length(); ++week){
            QList<int> weeklyStatusList;
            int completed = 0;
            int failed = 0;
            int inProgress = 0;
            for (int j = 1; j < 8; j++) { // go through each day of chosen week of month
                for ( int i = 0; i < tasksList.length(); ++i) {
                    QString status = tasksList.at(i).status();// because we start at June(6) till December(12)
                    if((tasksList.at(i).date().month() == (month+6)) && (tasksList.at(i).date().day() == (j+(7*week)))){
                        //   if { // go through all days
                        qDebug() << "Day: "<< tasksList.at(i).date().day() << "Week: "<< week+1<< ", Month: "<< month+6;
                        if ( status == "Completed")
                            ++completed;
                        else if ( status == "Failed")
                            ++failed;
                        else if  ( status == "In-Progress")
                            ++inProgress;
                    }
                }
            }
            qDebug() << "Completed: "<<  completed;
            qDebug() << "Failed:  "<< failed;
            qDebug() << "In-Progress: "<< inProgress;
            weeklyStatusList.append(completed);
            weeklyStatusList.append(failed);
            weeklyStatusList.append(inProgress);
            combinedMonths.append(weeklyStatusList);
        }
        monthlyMap.insert(month,combinedMonths);
    }
}

void StatisticsForm::printMap() const{
    for (int i = 0;i<months.length(); ++i) {
        printList(monthlyMap.value(i));
    }
}

void StatisticsForm::printList(QList<QList<int>> t_combinedList) const{
    for(int week = 0; week < weeks.length(); ++week){
        for(int state = 0; state < status.length() ; ++state){
            qDebug() << "Week: "<< week<< "Status: "<< state<< " "<< t_combinedList.at(week).at(state);
        }
    }
}

QList<Task> StatisticsForm::getTasksList() const
{
    return tasksList;
}

void StatisticsForm::setTasksList(const QList<Task> &value)
{
    tasksList = value;
}




