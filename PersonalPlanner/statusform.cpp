#include "statusform.h"
#include "ui_statusform.h"

StatusForm::StatusForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusForm)
{
    m_task = Task(-1,"", QDate(1,2,3), -1, "");
    ui->setupUi(this);
    this->setFixedSize(402, 300);
}


StatusForm::~StatusForm(){
    delete ui;
}


Task* StatusForm::readStatusFromWindow(){
    if(ui->completedRb->isChecked())
        status = "Completed";
    else if(ui->failedRb->isChecked())
        status = "Failed";
    else if(ui->inProgressRb->isChecked())
        status = "In-Progress";
    else{
     return &m_task;
    }

    m_task.setStatus(status);
    m_taskManager.update(m_task);

    return &m_task;
}


void StatusForm::giveTask(const Task &task){
    m_task = task;
}

void StatusForm::setStatus(const QString &value){
    status = value;
}


void StatusForm::initializeStatusForm(){
    if(status == "Completed")
        ui->completedRb->setChecked(true);
    else if(status == "Failed")
        ui->failedRb->setChecked(true);
    else if(status == "In-Progress")
        ui->inProgressRb->setChecked(true);
}

//Slots
void StatusForm::on_confirm_cancel_btn_accepted(){
    emit refreshGUI();
}


void StatusForm::on_confirm_cancel_btn_rejected(){
    this->close();
}

