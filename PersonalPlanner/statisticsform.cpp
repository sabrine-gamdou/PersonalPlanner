#include "statisticsform.h"
#include "ui_statisticsform.h"

StatisticsForm::StatisticsForm(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::StatisticsForm)
{

    ui->setupUi(this);
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

StatisticsForm::~StatisticsForm()
{
    delete ui;
}



void StatisticsForm::createStructure(){


    monthModel->setName("Statistic of your Task Status from June - December " + QString::number(QDate::currentDate().year()));

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
    createStructure();
    populateData();

    view->changeSeries(monthModel);
    view->setTitle(monthModel->name());

    view->axes(Qt::Horizontal).first()->setGridLineVisible(false);
    view->legend()->setVisible(true);
    view->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(view);
    chartView->setChart(view);
    setCentralWidget(chartView);
    resize(600,400);
    show();
}


void StatisticsForm::sortDateWeeks() {

    for(int month = 0; month < months.length(); ++month){
        QList<QList<int>> combinedMonths;
        for(int week = 0; week < weeks.length(); ++week){
            QList<int> weeklyStatusList;
            int completed = 0;
            int failed = 0;
            int inProgress = 0;
            for (int dayOfWeek = 1; dayOfWeek < 8; dayOfWeek++) { // go through each day of chosen week of month
                for ( int task = 0; task < tasksList.length(); ++task) {
                    if(tasksList.at(task).date().year() == QDate::currentDate().year()){
                    QString status = tasksList.at(task).status();
                    //check the first 28 days
                    if((tasksList.at(task).date().month() == (month+6)) && (tasksList.at(task).date().day() == (dayOfWeek+(7*week)))){
                        //this could also go in  a seperate method
                        if ( status == "Completed")
                            ++completed;
                        else if ( status == "Failed")
                            ++failed;
                        else if  ( status == "In-Progress")
                            ++inProgress;
                    }
                }
                }
            }
            //check days 29, 30 and 31 seperately
            //this could go in a seperate method
            //checked outside of days-loop, so they are checked only once per week and not 7 times
            for( int task = 0; task < tasksList.length(); ++task){
                QString status = tasksList.at(task).status();
                if((tasksList.at(task).date().month() == (month+6)) && (week == 3) && (tasksList.at(task).date().year() == QDate::currentDate().year()) && checkEndOfMonth(tasksList.at(task).date().day(), tasksList.at(task).date().month())){
                    if ( status == "Completed")
                        ++completed;
                    else if ( status == "Failed")
                        ++failed;
                    else if  ( status == "In-Progress")
                        ++inProgress;
                }
            }
            weeklyStatusList.append(completed);
            weeklyStatusList.append(failed);
            weeklyStatusList.append(inProgress);
            combinedMonths.append(weeklyStatusList);
        }
        monthlyMap.insert(month,combinedMonths);
    }
}


bool StatisticsForm::checkEndOfMonth(int day, int month){
    return ((((month == 7) || (month == 8) || (month == 10) || (month == 12)) && ((day == 29) || (day == 30) || (day == 31))) || (((month == 6) || (month == 9) || (month == 11)) && ((day == 29) || (day == 30))));
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




