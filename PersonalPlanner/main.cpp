#include <iostream>
#include "mainwindow.h"
#include "login.h"
#include "task.h"
#include <QApplication>
#include <QString>
#include <QCoreApplication>
#include <string>
#include "databasesingleton.h"
#include "taskdaoimp.h"
#include <QDebug>
#include <QTextCodec>

int main()
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //std::cout << "START" << std::endl;

    //QCoreApplication a(argc, argv);

    //Login l;
    //l.show();

   /* DatabaseSingleton* sin = DatabaseSingleton::getInstance();
    sin->openConnection();*/


   // std::string string = "task1";
    QString t_title("task1");
    QDate t_date(1997,07,26);
    Task task(1, t_title, t_date, 2);
    task.setDescription("This is task 1");
    task.setStatus("Completed");


    TaskDaoImp taskDao;

    bool state = taskDao.delete_(task);

    std::string string = task.toString().toUtf8().toStdString();

    //std::string string = taskDao.read(1)->toString().toUtf8().toStdString();
    qDebug() << "State: " << state;
    std::cout << string << std::endl;
//    std::cout << task.toString() << std::endl;
    //c.createTableFromData();
    //c.queryDataAndPrintData();



    return(0);
}
