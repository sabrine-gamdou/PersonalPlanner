#include "mainwindow.h"
#include "sqlconnector.h"
#include "login.h"
#include <QApplication>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //std::cout << "START" << std::endl;

    //QCoreApplication a(argc, argv);

    Login l;
    l.show();

    sqlconnector c;
    c.openConnection();
    c.createTableFromData();
    //c.queryDataAndPrintData();
    return a.exec();
}
