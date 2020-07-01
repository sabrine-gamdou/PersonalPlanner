#include "statisticsform.h"
#include "ui_statisticsform.h"

StatisticsForm::StatisticsForm(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::StatisticsForm)
{
    ui->setupUi(this);
    this->setFixedSize(500, 400);
    this->setStyleSheet("background-color: black");
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}


StatisticsForm::~StatisticsForm(){
    delete ui;
}

/*! \brief This method creates the drilldown structure. We first create our top level model, which we call monthModel.
 * For each month in monthModel we create a drilldown model called weeklyModel which contains more detailed data for that month.
 * In weeklyModel, we use the drilldown handler to bring us back to monthModel. To do so we add mapping to the model. The monthModel
 * is mapped to weeklyModel for each month. Every weeklyModel is mapped back to the monthModel. To make mapping work, we connect the
 * clicked signals from our model to the statisticView.*/
void StatisticsForm::createStructure(){
    monthModel->setName("<span style='font-family: URW Gothic L'>Statistic of your Task Status from June - December " +
                        QString::number(QDate::currentDate().year()) + "</span>");

    for (int month = 0; month < months.count(); month++) {
        weeklyModel = new StatisticModel (weeks, 10, view);
        monthModel->mapStatisticModel(month, weeklyModel);
        for ( int week = 0; week < weeks.count(); week++) {
            weeklyModel->mapStatisticModel(week, monthModel);
            weeklyModel->setName(QString("<span style='font-family: URW Gothic L'>Status by week - " + months.at(month) + " </span>"));
        }
        QObject::connect(weeklyModel, &StatisticModel::clicked, view, &StatisticView::handleClicked);
    }
    QObject::connect(monthModel, &StatisticModel::clicked, view, &StatisticView::handleClicked);
}

/*! \brief This method creates for every status a monthly and weekly QBarSet. The data will be read from the sorted QMap to the weeklyBarSet. The
 * monthlyBarSet data will be the sum of the weeklyBarSet data.
*/
void StatisticsForm::populateData(){
    QMap<int, QList<QList<int>>>::const_iterator month;

    for (const QString &state : status) {
        QBarSet *monthlyStatus = new QBarSet(state);
        int monthC = 0;
        for (month = monthlyMap.begin();month != monthlyMap.end();++month) {
            QBarSet *weeklyStatus = new QBarSet(state);
            for (int week = 0; week < weeks.count(); ++week)
                *weeklyStatus <<  month.value().at(week).at(statusToInt(state));
            ++monthC;
            monthModel->statisticModel(month.key())->append(weeklyStatus);
            *monthlyStatus << weeklyStatus->sum();
        }
        monthModel->append(monthlyStatus);
    }
}


int StatisticsForm::statusToInt(const QString &status){
    if(status == "Completed")
        return 0;
    else if(status == "Failed")
        return 1;
    else if(status == "In-Progress")
        return 2;

    return -1;
}

/*! \brief This method creates a view and a model, sorts the QMap, creates the structure and populates the data. Initializes the view to the monthlyModel and sets
 * the given title. */
void StatisticsForm::initializeChart(){
    view = new StatisticView();
    monthModel = new StatisticModel(months, 40, view);

    sortDateWeeks();
    createStructure();
    populateData();

    view->changeSeries(monthModel);
    view->setTitle(monthModel->name());

    QFont f("URW Gothic L");

    view->axes(Qt::Horizontal).first()->setGridLineVisible(false);
    view->legend()->setVisible(true);
    view->legend()->setAlignment(Qt::AlignBottom);
    view->legend()->setFont(f);

    QChartView *chartView = new QChartView(view);
    chartView->setChart(view);
    setCentralWidget(chartView);
    resize(600,400);
    show();
}

/*! \brief This method mainly sorts the dates after months and weeks and counts the statuses of each week. The status counters will be saved in a corresponding List.
 * Afterwards the List is stored in another combinedMonths List. Each combinedMonths List is mapped to a corresponging integer value (describing a month). */
void StatisticsForm::sortDateWeeks(){
    for(int month = 0; month < months.length(); ++month){ //go through all months
        QList<QList<int>> combinedMonths;
        for(int week = 0; week < weeks.length(); ++week){ //go through the 4 weeks of each month
            QList<int> weeklyStatusList;
            completed = 0;
            failed = 0;
            inProgress = 0;
            for ( int task = 0; task < tasksList.length(); ++task) {
                QString status = tasksList.at(task).status();
                for (int dayOfWeek = 1; dayOfWeek < 8; dayOfWeek++) { // go through each day of chosen week of month
                    if(tasksList.at(task).date().year() == QDate::currentDate().year()) //check the day and count status ONLY if its a day of the current year
                        //count the status for the first 28 days
                        if((tasksList.at(task).date().month() == (month+6)) && (tasksList.at(task).date().day() == (dayOfWeek+(7*week)))) countStatus(status);
                }
                /*count status for the days 29, 30 and 31 seperately (checked outside of days-loop, so they are checked only once per week and not 7 times)
                 *if the task has a date of current year AND month = given month AND it is the 4th week of the month (week == 3, cause week counter starts at 0)
                 *AND day is either 29/30/31 THEN count status!*/
                if((tasksList.at(task).date().month() == (month+6)) && (week == 3) && (tasksList.at(task).date().year() == QDate::currentDate().year()) &&
                        checkEndOfMonth(tasksList.at(task).date().day(), tasksList.at(task).date().month()))
                    countStatus(status);
            }
            weeklyStatusList.append(completed);
            weeklyStatusList.append(failed);
            weeklyStatusList.append(inProgress);
            combinedMonths.append(weeklyStatusList);
        }
        monthlyMap.insert(month,combinedMonths);
    }
}


void StatisticsForm::countStatus(const QString &status){
    if(status == "Completed")
        ++completed;
    else if (status == "Failed")
        ++failed;
    else if  (status == "In-Progress")
        ++inProgress;
}

/*! \brief This method checks the end of the month.
 * returns true if the months == 7,8,10 or 12 AND the day is 29,30 or 31
 * OR if the months == 6,9 or 11 AND the day is 29 or 30.
 * This method is meant to differentiate between months with 30 or 31 days. */
bool StatisticsForm::checkEndOfMonth(int day, int month){
    return ((((month == 7) || (month == 8) || (month == 10) || (month == 12)) && ((day == 29) || (day == 30) || (day == 31))) ||
            (((month == 6) || (month == 9) || (month == 11)) && ((day == 29) || (day == 30))));
}


void StatisticsForm::setTasksList(const QList<Task> &value){
    tasksList = value;
}




