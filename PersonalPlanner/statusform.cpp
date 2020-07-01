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
        m_status = "Completed";
    else if(ui->failedRb->isChecked())
        m_status = "Failed";
    else if(ui->inProgressRb->isChecked())
        m_status = "In-Progress";
    else{
     return &m_task;
    }

    m_task.setStatus(m_status);
    m_taskManager.update(m_task);

    return &m_task;
}


void StatusForm::giveTask(const Task &task){
    m_task = task;
}

void StatusForm::setStatus(const QString &value){
    m_status = value;
}


void StatusForm::initializeStatusForm(){
    if(m_status == "Completed")
        ui->completedRb->setChecked(true);
    else if(m_status == "Failed")
        ui->failedRb->setChecked(true);
    else if(m_status == "In-Progress")
        ui->inProgressRb->setChecked(true);
}

//Slots
void StatusForm::on_confirm_cancel_btn_accepted(){
    emit refreshGUI();
}


void StatusForm::on_confirm_cancel_btn_rejected(){
    this->close();
}

