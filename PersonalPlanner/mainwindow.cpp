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

    ui->setupUi(this);
    ui->taskView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    QObject::connect(ui->editInfoCheckBox, &QCheckBox::stateChanged, this, &MainWindow::editInfoCheckBox_checked);
    QObject::connect(ui->menuLogOut, &QMenu::triggered, this, &MainWindow::menuLogOut_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::getUserData(){

    User t_user=  this->m_userManager.read(m_username);

    qDebug() << t_user.toString();
    ui->firstnameTxt->setText(t_user.firstname());
    ui->lastnameTxt->setText(t_user.lastname());
    ui->emailTxt->setText(t_user.email());
    ui->dateEdit->setDate(t_user.birthday());
    ui->addressTxt->setText(t_user.address());
}


void MainWindow::getTasks(){
    m_taskManager.readAll(m_username);

    ui->taskView->setModel(m_taskManager.getTaskModel());
    ui->taskView->horizontalHeader()->setVisible(true);

    ui->taskView->show();
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



void MainWindow::on_saveChangesBtn_clicked()
{
    User m_user(m_username, m_password, "", "", "");
    bool stop = false;


    if(ui->firstnameTxt->text() == "")
    {
        ui->firstnameTxt->setStyleSheet("border: 1px solid red");
        ui->firstnameTxt->setPlaceholderText("First Name EMPTY!");
        stop = true;
    }else{
        ui->firstnameTxt->setStyleSheet("");
        m_user.setFirstname(ui->firstnameTxt->text());
        stop = false;
    }


    if(ui->lastnameTxt->text() == "")
    {
        ui->lastnameTxt->setStyleSheet("border: 1px solid red");
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        stop = false;
    }else{
        ui->lastnameTxt->setStyleSheet("");
        m_user.setLastname(ui->lastnameTxt->text());
        stop = false;
    }


    if(ui->emailTxt->text() == "")
    {
        ui->emailTxt->setStyleSheet("border: 1px solid red");
        ui->emailTxt->setPlaceholderText("E-mail EMPTY!");
        stop = true;
    }else{
        ui->emailTxt->setStyleSheet("");
        m_user.setEmail(ui->emailTxt->text());
        stop = false;
    }

    m_user.setBirthday(ui->dateEdit->date());
    m_user.setAddress(ui->addressTxt->text());

    if(!stop){
        userUpdatedConfirmed(m_userManager.update(m_user));
    }
}

void MainWindow::userUpdatedConfirmed(const bool t_userUpdated){
    qDebug() << "User Updated status: "<< t_userUpdated;
    if(t_userUpdated){
        QMessageBox::information(this, "Information", "You successfully updated your profile information!");
    }else{
        QMessageBox::warning(this, "Warning", "Something went wrong ... Please try again later.");
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



void MainWindow::readTaskFromMainWindow() {

    Task new_task (0, ui->titleTxt->text(), ui->dateTimeEdit->date(), ui->importanceSb->text().toInt(), m_username);
    new_task.setDescription(ui->descriptionTxt->text());
    new_task.setRepetition(ui->repeatCb->currentText());

    qDebug() <<  "TaskManager created" << m_taskManager.create(new_task, m_username);

}


void MainWindow::on_confirm_cancelBtnB_accepted()
{
    readTaskFromMainWindow();
    getTasks();
}


void MainWindow::on_confirm_cancelBtnB_rejected()
{
    ui->titleTxt->clear();
    ui->dateTimeEdit->clear();
    ui->descriptionTxt->clear();
    ui->importanceSb->clear();

}


void MainWindow::on_deleteBtn_clicked()
{
    QModelIndex index = ui->taskView->selectionModel()->currentIndex();

    int taskID = m_taskManager.getTaskModel()->taskIDList().at(index.row());

    qDebug() << "list size" << m_taskManager.getTaskModel()->taskIDList().size();

    qDebug() << "Task deleted: " << index.row() << m_taskManager.delete_(taskID);

    m_taskManager.getTaskModel()->removeRow(ui->taskView->currentIndex().row(), 1 , ui->taskView->currentIndex());

    m_taskManager.setTaskIDList(m_taskManager.getTaskModel()->taskIDList());

    ui->deleteBtn->setEnabled(false);
}


void MainWindow::on_taskView_pressed()
{
    ui->deleteBtn->setEnabled(true);
    ui->editBtn->setEnabled(true);
}



void MainWindow::on_editBtn_clicked()
{
    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    QVariant value = index.sibling(index.row(),index.column()).data();
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


