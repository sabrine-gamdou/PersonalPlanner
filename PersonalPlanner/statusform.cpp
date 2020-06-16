#include "statusform.h"
#include "ui_statusform.h"

StatusForm::StatusForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusForm)
{
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

void StatusForm::readStatusFromWindow() {
    if(ui->completedRb->isChecked()){
        status = "Completed";
    } else if(ui->failedRb->isChecked()){
        status = "Failed";
    } else if(ui->inProgressRb->isChecked()){
        status = "In-Progress";
    }
}

void StatusForm::on_confirm_cancel_btn_accepted()
{
    readStatusFromWindow();
}

void StatusForm::on_confirm_cancel_btn_rejected()
{
    this->close();
}
