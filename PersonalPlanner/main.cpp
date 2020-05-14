#include "mainwindow.h"
#include "sqlconnector.h"
#include <QApplication>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //std::cout << "START" << std::endl;

    //QCoreApplication a(argc, argv);

    sqlconnector c;
    c.openConnection();
    c.createTableFromData();
    //c.queryDataAndPrintData();
    return a.exec();
}
