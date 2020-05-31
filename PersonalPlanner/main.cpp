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

    Login l;
    l.show();

    return a.exec();
}
