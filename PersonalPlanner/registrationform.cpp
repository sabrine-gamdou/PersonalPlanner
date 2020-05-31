#include "registrationform.h"
#include "ui_registrationform.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    ui->setupUi(this);

    ui->passTxt->setEchoMode(QLineEdit::Password);
    ui->passTxt->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}


void RegistrationForm::on_confirmBtn_clicked(){

    QString un;
    QString pass;
    QString firstname;
    QString lastname;
    QString email;

    bool stop = false;


    if(ui->usernameTxt->text() == "")
    {
        ui->usernameTxt->setStyleSheet("border: 1px solid red");
        ui->usernameTxt->setPlaceholderText("Username EMPTY!");
        stop = true;
    }else{
        ui->usernameTxt->setStyleSheet("");
        un = ui->usernameTxt->text();
        stop = false;
    }



    if(ui->passTxt->text() == "")
    {
        ui->passTxt->setStyleSheet("border: 1px solid red");
        ui->passTxt->setPlaceholderText("Password EMPTY!");
        stop = true;
    }else{
        ui->passTxt->setStyleSheet("");
        pass = ui->passTxt->text();
        stop = false;
    }




    if(ui->firstnameTxt->text() == "")
    {
        ui->firstnameTxt->setStyleSheet("border: 1px solid red");
        ui->firstnameTxt->setPlaceholderText("First Name EMPTY!");
        stop = true;
    }else{
        ui->firstnameTxt->setStyleSheet("");
        firstname = ui->firstnameTxt->text();
        stop = false;
    }




    if(ui->lastnameTxt->text() == "")
    {
        ui->lastnameTxt->setStyleSheet("border: 1px solid red");
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        stop = false;
    }else{
        ui->lastnameTxt->setStyleSheet("");
        lastname = ui->lastnameTxt->text();
        stop = false;
    }




    if(ui->emailTxt->text() == "")
    {
        ui->emailTxt->setStyleSheet("border: 1px solid red");
        ui->emailTxt->setPlaceholderText("E-mail EMPTY!");
        stop = true;
    }else{
        ui->emailTxt->setStyleSheet("");
        email = ui->emailTxt->text();
        stop = false;
    }


    //check if username available
    //check if email available

    if(stop){
        ui->errLb->setStyleSheet("border: 1px solid red");
        ui->errLb->setEnabled(true);
        ui->errLb->setText("Please correct your mistakes.");
    }else{
        ui->errLb->setText("");
        ui->errLb->setEnabled(false);
        User t_user(un,pass,firstname,lastname,email);
        userCreatedConfirmed(m_userManager->create(t_user));
    }
}




void RegistrationForm::on_cancelBtn_clicked(){
    this->close();
}




void RegistrationForm::userCreatedConfirmed(const bool t_userCreated){
    qDebug() << "Bug here"<< t_userCreated;
    if(t_userCreated){
        QMessageBox::information(this, "Information", "Welcome to Personal Planner!");
        this->close();
    }else{
        QMessageBox::warning(this, "Warning", "Something went wrong ... Please try again later.");
    }

}
