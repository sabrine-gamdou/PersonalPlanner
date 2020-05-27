#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QFile File("stylesheet.qss");
//    File.open(QFile::ReadOnly);
//    QString StyleSheet = QLatin1String(File.readAll());

//    this->setStyleSheet(StyleSheet);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
