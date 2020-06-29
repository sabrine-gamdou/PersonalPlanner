#include "statusform.h"
#include "ui_statusform.h"


StatusForm::StatusForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusForm)
{
    m_task = Task(-1,"", QDate(1,2,3), -1, "");
    ui->setupUi(this);
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

    m_task.setStatus(status);
    m_taskManager.update(m_task);

    return &m_task;
}

void StatusForm::giveTask(const Task &task){
    m_task = task;
}

//Slots
void StatusForm::on_confirm_cancel_btn_accepted(){
    emit refreshGUI();
}

void StatusForm::on_confirm_cancel_btn_rejected(){
    this->close();
}
