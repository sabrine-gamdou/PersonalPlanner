#include <iostream>
#include "login.h"
#include "task.h"
#include <QApplication>
#include <QString>
#include <QCoreApplication>
#include <string>
#include "databasesingleton.h"
#include "taskdaoimp.h"
#include "userdaoimp.h"
#include "user.h"
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication a(argc, argv);
   // MainWindow w;
   // w.show();
    //std::cout << "START" << std::endl;



    Login l;
    l.show();

   /* DatabaseSingleton* sin = DatabaseSingleton::getInstance();
    sin->openConnection();*/


   // std::string string = "task1";
//    QString t_title("task1");
//    QDate t_date(1997,07,26);
//    Task task(1, t_title, t_date, 2);
//    task.setDescription("This is task 1");
//    task.setStatus("Completed");


//    TaskDaoImp taskDao;

//    bool state = taskDao.create(task);

//    std::string string = task.toString().toUtf8().toStdString();

   // std::string string = taskDao.read(1)->toString().toUtf8().toStdString();
   // qDebug() << "State: " << state;
   // std::cout << string << std::endl;
//    std::cout << task.toString() << std::endl;
    //c.createTableFromData();
    //c.queryDataAndPrintData();

//    QString username("user1");
//    QString password("pass1");
//    QString firstname("sab");
//    QString lastname("gam");
//    QString email("@somthign");
//    QString address("Street1");

//   User user( username, password, firstname, lastname, email);

//   user.setBirthday(t_date);
//   user.setAddress(address);

   //std::string str = user.toString().toUtf8().toStdString();

  // UserDaoImp userDao;

   //bool stt = userDao.create(user);



   //qDebug() << "User State: " << stt;
   //std::cout << str << std::endl;


    return a.exec();
}
