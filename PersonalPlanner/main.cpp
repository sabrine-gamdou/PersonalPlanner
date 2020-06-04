#include "login.h"
#include "task.h"
#include "user.h"
#include "databasesingleton.h"
#include "taskdaoimp.h"
#include "userdaoimp.h"
#include <QDebug>
#include <QTextCodec>
#include <string>
#include <iostream>
#include <QCoreApplication>
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login l;
    l.show();

    return a.exec();
}
