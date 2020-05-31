#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QFile File("stylesheet.qss");
//    File.open(QFile::ReadOnly);
//    QString StyleSheet = QLatin1String(File.readAll());

//    this->setStyleSheet(StyleSheet);
    //QObject::connect(ui->editInfoCheckBox, &QCheckBox::stateChanged, this, &MainWindow::on_editInfoCheckBox_clicked);

    ui->setupUi(this);
    //this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
   //QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(editInfoCheckBox_checked(bool)));
   QObject::connect(ui->editInfoCheckBox, &QCheckBox::stateChanged, this, &MainWindow::editInfoCheckBox_checked);
   QObject::connect(ui->menuLogOut, &QMenu::triggered, this, &MainWindow::menuLogOut_clicked);
//   QObject::connect(ui->logoutBtn, &QCommandLinkButton::clicked, this, &MainWindow::on_logoutBtn_clicked);
//   QObject::connect(ui->deleteAccountBtn, &QCommandLinkButton::clicked, this, &MainWindow::on_deleteAccountBtn_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getTasks(){

}

void MainWindow::getUserData(){
    User *t_user=  this->m_userManager.read(m_username);
    qDebug() << t_user->toString();
    ui->firstnameTxt->setText(t_user->firstname());
    ui->lastnameTxt->setText(t_user->lastname());
    ui->emailTxt->setText(t_user->email());
    ui->dateEdit->setDate(t_user->birthday());
    ui->addressTxt->setText(t_user->address());


    //move to seperate method
    //ui->editInfoCheckBox->setChecked(false);
}


void MainWindow::editInfoCheckBox_checked(const bool checked){

    ui->firstnameTxt->setEnabled(checked);
    ui->lastnameTxt->setEnabled(checked);
    ui->emailTxt->setEnabled(checked);
    ui->dateEdit->setEnabled(checked);
    ui->addressTxt->setEnabled(checked);

    ui->saveChangesBtn->setEnabled(checked);

}


void MainWindow::on_deleteAccountBtn_clicked(){
    if(QMessageBox(QMessageBox::Question,
                                           "Login System", "Are you sure you want to delete your account?",
                                       QMessageBox::Yes|QMessageBox::No).exec()){
        m_userManager.delete_(this->m_username);
    }

}

void MainWindow::logout(){
    this->m_username = "";
    this->m_password = "";
    this->close();
}

void MainWindow::on_logoutBtn_clicked(){
   logout();
}

void MainWindow::menuLogOut_clicked(){
    logout();
}

QString MainWindow::username() const
{
    return m_username;
}

void MainWindow::setUsername(const QString &username)
{
    m_username = username;
}

QString MainWindow::password() const
{
    return m_password;
}

void MainWindow::setPassword(const QString &password)
{
    m_password = password;
}
