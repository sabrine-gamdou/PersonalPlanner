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
    p_monthModel->setName("<span style='font-family: URW Gothic L'>Statistic of your Task Status from June - December " +
                        QString::number(QDate::currentDate().year()) + "</span>");

    for (int month = 0; month < m_months.count(); month++) {
        p_weeklyModel = new StatisticModel (m_weeks, 10, p_view);
        p_monthModel->mapStatisticModel(month, p_weeklyModel);
        for ( int week = 0; week < m_weeks.count(); week++) {
            p_weeklyModel->mapStatisticModel(week, p_monthModel);
            p_weeklyModel->setName(QString("<span style='font-family: URW Gothic L'>Status by week - " + m_months.at(month) + " </span>"));
        }
        QObject::connect(p_weeklyModel, &StatisticModel::clicked, p_view, &StatisticView::handleClicked);
    }
    QObject::connect(p_monthModel, &StatisticModel::clicked, p_view, &StatisticView::handleClicked);
}

/*! \brief This method creates for every status a monthly and weekly QBarSet. The data will be read from the sorted QMap to the weeklyBarSet. The
 * monthlyBarSet data will be the sum of the weeklyBarSet data.
*/
void StatisticsForm::populateData(){
    QMap<int, QList<QList<int>>>::const_iterator month;

    for (const QString &state : m_status) {
        QBarSet *monthlyStatus = new QBarSet(state);
        int monthC = 0;
        for (month = m_monthlyMap.begin();month != m_monthlyMap.end();++month) {
            QBarSet *weeklyStatus = new QBarSet(state);
            for (int week = 0; week < m_weeks.count(); ++week)
                *weeklyStatus <<  month.value().at(week).at(statusToInt(state));
            ++monthC;
            p_monthModel->statisticModel(month.key())->append(weeklyStatus);
            *monthlyStatus << weeklyStatus->sum();
        }
        p_monthModel->append(monthlyStatus);
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
    p_view = new StatisticView();
    p_monthModel = new StatisticModel(m_months, 40, p_view);

    sortDateWeeks();
    createStructure();
    populateData();

    p_view->changeSeries(p_monthModel);
    p_view->setTitle(p_monthModel->name());

    QFont f("URW Gothic L");

    p_view->axes(Qt::Horizontal).first()->setGridLineVisible(false);
    p_view->legend()->setVisible(true);
    p_view->legend()->setAlignment(Qt::AlignBottom);
    p_view->legend()->setFont(f);

    QChartView *chartView = new QChartView(p_view);
    chartView->setChart(p_view);
    setCentralWidget(chartView);
    resize(600,400);
    show();
}

/*! \brief This method mainly sorts the dates after months and weeks and counts the statuses of each week. The status counters will be saved in a corresponding List.
 * Afterwards the List is stored in another combinedMonths List. Each combinedMonths List is mapped to a corresponging integer value (describing a month). */
void StatisticsForm::sortDateWeeks(){
    for(int month = 0; month < m_months.length(); ++month){ //go through all months
        QList<QList<int>> combinedMonths;
        for(int week = 0; week < m_weeks.length(); ++week){ //go through the 4 weeks of each month
            QList<int> weeklyStatusList;
            m_completed = 0;
            m_failed = 0;
            m_inProgress = 0;
            for ( int task = 0; task < m_tasksList.length(); ++task) {
                QString status = m_tasksList.at(task).status();
                for (int dayOfWeek = 1; dayOfWeek < 8; dayOfWeek++) { // go through each day of chosen week of month
                    if(m_tasksList.at(task).date().year() == QDate::currentDate().year()) //check the day and count status ONLY if its a day of the current year
                        //count the status for the first 28 days
                        if((m_tasksList.at(task).date().month() == (month+6)) && (m_tasksList.at(task).date().day() == (dayOfWeek+(7*week)))) countStatus(status);
                }
                /*count status for the days 29, 30 and 31 seperately (checked outside of days-loop, so they are checked only once per week and not 7 times)
                 *if the task has a date of current year AND month = given month AND it is the 4th week of the month (week == 3, cause week counter starts at 0)
                 *AND day is either 29/30/31 THEN count status!*/
                if((m_tasksList.at(task).date().month() == (month+6)) && (week == 3) && (m_tasksList.at(task).date().year() == QDate::currentDate().year()) &&
                        checkEndOfMonth(m_tasksList.at(task).date().day(), m_tasksList.at(task).date().month()))
                    countStatus(status);
            }
            weeklyStatusList.append(m_completed);
            weeklyStatusList.append(m_failed);
            weeklyStatusList.append(m_inProgress);
            combinedMonths.append(weeklyStatusList);
        }
        m_monthlyMap.insert(month,combinedMonths);
    }
}


void StatisticsForm::countStatus(const QString &status){
    if(status == "Completed")
        ++m_completed;
    else if (status == "Failed")
        ++m_failed;
    else if  (status == "In-Progress")
        ++m_inProgress;
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
    m_tasksList = value;
}




