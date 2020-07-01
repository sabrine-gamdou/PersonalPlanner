#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include "statisticmodel.h"
#include "statisticview.h"
#include "taskdaoimp.h"

#include <QMainWindow>
#include <QDesktopWidget>
#include <QChart>
#include <QApplication>
#include <QChartView>
#include <QBarSet>
#include <QLegend>
#include <QMap>

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
        "<span style='font-family: URW Gothic L'>Jun</span>", "<span style='font-family: URW Gothic L'>Jul</span>", "<span style='font-family: URW Gothic L'>Aug</span>", "<span style='font-family: URW Gothic L'>Sep</span>",
        "<span style='font-family: URW Gothic L'>Oct</span>", "<span style='font-family: URW Gothic L'>Nov</span>", "<span style='font-family: URW Gothic L'>Dec</span>"
    };
    const QStringList weeks = {
        "<span style='font-family: URW Gothic L'>week 1</span>", "<span style='font-family: URW Gothic L'>week 2</span>", "<span style='font-family: URW Gothic L'>week 3</span>", "<span style='font-family: URW Gothic L'>week 4</span>"
    };
    const QStringList status = {
        "Completed", "In-Progress", "Failed"
    };

    int completed;
    int failed;
    int inProgress;
};
#endif // STATISTICSFORM_H
