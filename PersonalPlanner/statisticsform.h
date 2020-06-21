#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include "statisticmodel.h"
#include "statisticview.h"
#include "taskdaoimp.h"

namespace Ui {
class StatisticsForm;
}

class StatisticsForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsForm(QWidget *parent = 0);
    ~StatisticsForm();
    void createStructure();
    void populateData();
    void initializeData();
    void sortDateMonths(int month);
    void sortDateWeeks(int month, int week);
    StatisticView *getView() const;
    void setUsername(const QString &value);


private:
    Ui::StatisticsForm *ui;

    StatisticModel monthModel;
    StatisticModel *weeklyModel;
    StatisticView *view;
    TaskDaoImp m_taskManager;
    QString username;

    QList<int> statusMonthlyList;
    QList<int> statusListStatistic;
    QList<QList<int>> combinedList;




    //Define categories
    const QStringList months = {
        "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    const QStringList weeks = {
        "week 1", "week 2", "week 3", "week 4"
    };
    const QStringList status = {
        "Completed", "In-Progress", "Failed"
    };
};
#endif // STATISTICSFORM_H
