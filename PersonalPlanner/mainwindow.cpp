#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tasklistmodel.h"
#include "taskdaoimp.h"


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
    QObject::connect(ui->editInfoCheckBox, &QCheckBox::stateChanged, this, &MainWindow::editInfoCheckBox_checked);
    QObject::connect(ui->menuLogOut, &QMenu::triggered, this, &MainWindow::menuLogOut_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getTasks(){

}

void MainWindow::getUserData(){
    User t_user=  this->m_userManager.read(m_username);
    qDebug() << t_user.toString();
    ui->firstnameTxt->setText(t_user.firstname());
    ui->lastnameTxt->setText(t_user.lastname());
    ui->emailTxt->setText(t_user.email());
    ui->dateEdit->setDate(t_user.birthday());
    ui->addressTxt->setText(t_user.address());
    m_taskManager.readAll(m_username);


    ui->taskView->setModel(m_taskManager.getTaskModel());
    ui->taskView->horizontalHeader()->setVisible(true);
    m_taskManager.getTaskModel()->populateData(m_taskManager.getTitleList(), m_taskManager.getDateList(), m_taskManager.getDescriptionList(), m_taskManager.getImportanceList(), m_taskManager.getRepetitionList());

    ui->taskView->show();
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


void MainWindow::readTaskFromMainWindow() {
    Task new_task (0, ui->titleTxt->text(), ui->dateTimeEdit->date(), ui->importanceSb->text().toInt(), m_username);
    new_task.setDescription(ui->descriptionTxt->text());
    new_task.setRepetition(ui->repeatCb->currentText());

    qDebug() <<  "TaskManager created" << m_taskManager.create(new_task, m_username);

}


void MainWindow::on_confirm_cancelBtnB_accepted()
{
    MainWindow::readTaskFromMainWindow();
}


void MainWindow::on_confirm_cancelBtnB_rejected()
{
    ui->titleTxt->clear();
    ui->dateTimeEdit->clear();
    ui->descriptionTxt->clear();
    ui->importanceSb->clear();

}
void MainWindow::on_tabWidget_tabBarClicked()
{  
    m_taskManager.readAll(m_username);
    ui->taskView->setModel(m_taskManager.getTaskModel());
}



void MainWindow::on_deleteBtn_clicked()
{
    m_taskManager.getTaskModel()->removeRow(ui->taskView->currentIndex().row(), 1 , ui->taskView->currentIndex());
    ui->deleteBtn->setEnabled(false);
}

void MainWindow::on_taskView_pressed()
{

    ui->taskView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->deleteBtn->setEnabled(true);
}
