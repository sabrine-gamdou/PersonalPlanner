#include "mainwindow.h"
#include "sqlconnector.h"
#include "loginForm.h"
#include "user.h"
#include "userhandler.h"
#include <string>
#include <iostream>
#include <QApplication>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    //std::cout << "START" << std::endl;

    //QCoreApplication a(argc, argv);

    Login l;
    //l.show();

    Sqlconnector c;
    c.connect();

    User user1("Anastasiya", "hallo");
    UserHandler uh1;



   //qDebug() << uh1.newUser(user1);
    std::cout << user1.toString();
   std::cout << uh1.getUser("Anastasiya")->toString();

    //c.openConnection();
    //c.createTableFromData();
    //c.queryDataAndPrintData();
    return a.exec();
}
