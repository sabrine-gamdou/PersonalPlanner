#include "helpform.h"
#include "ui_helpform.h"

HelpForm::HelpForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpForm)
{
    ui->setupUi(this);
    this->setFixedSize(1064, 592);
}

HelpForm::~HelpForm(){
    delete ui;
}
