#include "statusform.h"
#include "ui_statusform.h"


StatusForm::StatusForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusForm)
{
    m_task = Task(-1,"", QDate(1,2,3), -1, "");
    ui->setupUi(this);
}

StatusForm::~StatusForm()
{
    delete ui;
}

QString StatusForm::getStatus() const
{

    return status;
}

void StatusForm::setStatus(const QString &value)
{
    status = value;
}

void StatusForm::giveTask(Task &task){
    m_task = task;
}

Task* StatusForm::readStatusFromWindow() {
    if(ui->completedRb->isChecked()){
        status = "Completed";
    } else if(ui->failedRb->isChecked()){
        status = "Failed";
    } else if(ui->inProgressRb->isChecked()){
        status = "In-Progress";
    }
    m_task.setStatus(status);
    m_taskDao.update(m_task);


    return &m_task;
}

void StatusForm::on_confirm_cancel_btn_accepted()
{
    emit refreshGUI();
}

void StatusForm::on_confirm_cancel_btn_rejected()
{
    this->close();
}
