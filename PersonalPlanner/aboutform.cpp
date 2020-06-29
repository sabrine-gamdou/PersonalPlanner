#include "aboutform.h"
#include "ui_aboutform.h"

AboutForm::AboutForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutForm)
{
    ui->setupUi(this);
    this->setFixedSize(699, 500);
}

AboutForm::~AboutForm(){
    delete ui;
}
