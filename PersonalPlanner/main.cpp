#include "login.h"

#include <QCoreApplication>
#include <QApplication>


/* Our application starts with the LoginForm. */
int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    Login l;
    l.show();

    return a.exec();
}
