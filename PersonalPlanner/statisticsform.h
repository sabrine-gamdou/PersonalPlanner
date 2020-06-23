#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QMainWindow>
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
    void initializeChart();
    void sortDateWeeks();
    void printMap() const;
    void printList(QList<QList<int>> t_combinedList) const;
    int statusToInt(QString status);
    QList<Task> getTasksList() const;
    void setTasksList(const QList<Task> &value);
    bool checkEndOfMonth(int day, int month);


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
};
#endif // STATISTICSFORM_H
