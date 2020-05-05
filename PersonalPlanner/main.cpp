#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
<<<<<<< HEAD
    w.show();
    std::cout << "START" << std::endl;
=======
//    w.show();

>>>>>>> d45371f68de6e4f5bb76f11ed23ae9eeb20847d0
    return a.exec();
}
