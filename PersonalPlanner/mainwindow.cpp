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
    setStatus();
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
    QString style = "border: 1px solid red" ;

    if(ui->firstnameTxt->text() == "")
    {
        ui->firstnameTxt->setStyleSheet(style);
        ui->firstnameTxt->setPlaceholderText("First Name EMPTY!");
        stop = true;
    }else{
        ui->firstnameTxt->setStyleSheet("");
        m_user.setFirstname(ui->firstnameTxt->text());
        stop = false;
    }


    if(ui->lastnameTxt->text() == "")
    {
        ui->lastnameTxt->setStyleSheet(style);
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        stop = false;
    }else{
        ui->lastnameTxt->setStyleSheet("");
        m_user.setLastname(ui->lastnameTxt->text());
        stop = false;
    }


    if(ui->emailTxt->text() == "")
    {
        ui->emailTxt->setStyleSheet(style);
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
    new_task.setStatus(readStatusFromWindow());

    qDebug() <<  "TaskManager created" << m_taskManager.create(new_task, m_username);

}

QString MainWindow::readStatusFromWindow(){
    if(ui->rbCompleted->isChecked()){
        return "Completed";
    }else if(ui->rbInProgress->isChecked()){
        return "In-Progress";
    }else if(ui->rbFailed->isChecked()){
        return "Failed";
    }
    return "";
}

void MainWindow::on_confirm_cancelBtnB_accepted() {
    readTaskFromMainWindow();
    getTasks();
}


void MainWindow::on_confirm_cancelBtnB_rejected() {
    ui->titleTxt->clear();
    ui->dateTimeEdit->clear();
    ui->descriptionTxt->clear();
    ui->importanceSb->clear();

}

void MainWindow::deleteTask () {
    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

    m_taskManager.getTaskModel()->removeRow( index.row(),1 , index);

    qDebug() << "list size" << m_taskManager.getTaskModel()->taskList().size();

    qDebug() << "Task deleted: " << index.row() << m_taskManager.delete_(task);

    m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());

    ui->deleteBtn->setEnabled(false);

}

void MainWindow::on_deleteBtn_clicked() {
    deleteTask();
    ui->deleteBtn->setEnabled(false);
}


void MainWindow::on_taskView_pressed() {
    ui->deleteBtn->setEnabled(ui->taskView->currentIndex().isValid());
    ui->editBtn->setEnabled(ui->taskView->currentIndex().isValid());
}

void MainWindow::setStatus(){

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(50,205,50));
    ui->lbCompleted->setAutoFillBackground(true);
    ui->lbCompleted->setPalette(palette);

    palette.setColor(QPalette::Window, QColor(255,215,0));
    ui->lbInProgress->setAutoFillBackground(true);
    ui->lbInProgress->setPalette(palette);

    palette.setColor(QPalette::Window, QColor(220,220,220));
    ui->lbFailed->setAutoFillBackground(true);
    ui->lbFailed->setPalette(palette);
}

void MainWindow::on_editBtn_clicked() {

    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

   // m_taskManager.getTaskModel()->removeRow( index.row(),1 , index);
    ui->tabWidget->setCurrentIndex(1);

    ui->titleTxt->setText(task.title());
    ui->descriptionTxt->setText(task.description());
    ui->importanceSb->setValue(task.importance());
    ui->dateTimeEdit->setDate(task.date());
    ui->repeatCb->setCurrentIndex();

    m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());

    ui->deleteBtn->setEnabled(false);
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


