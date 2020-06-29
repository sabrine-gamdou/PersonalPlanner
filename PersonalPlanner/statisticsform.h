#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QtCharts/QChart>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QMap>
#include "statisticmodel.h"
#include "statisticview.h"
#include "taskdaoimp.h"

namespace Ui {
class StatisticsForm;
}

class StatisticsForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatisticsForm(QMainWindow *parent = 0);
    ~StatisticsForm();

    void createStructure();
    void populateData();
    int statusToInt(const QString &status);
    void initializeChart();
    void sortDateWeeks();
    void countStatus(const QString &status);
    bool checkEndOfMonth(int day, int month);
    void setTasksList(const QList<Task> &value);

private:
    Ui::StatisticsForm *ui;

    StatisticModel *monthModel;
    StatisticModel *weeklyModel;
    StatisticView *view;

    QList<Task> tasksList;
    QMap<int,QList<QList<int>>> monthlyMap;

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

    int completed;
    int failed;
    int inProgress;
};
#endif // STATISTICSFORM_H
