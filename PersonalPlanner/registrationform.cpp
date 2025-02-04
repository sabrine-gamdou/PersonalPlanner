#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    this->setFixedSize(381, 359);
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    ui->setupUi(this);

    ui->passTxt->setEchoMode(QLineEdit::Password);
    ui->passTxt->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

}

RegistrationForm::~RegistrationForm(){
    delete ui;
}

/*! \brief This method will notify the user with a messageBox if the given bool value is true an informationBox will be shown. Otherwise
 * a warningBox will show up. */
void RegistrationForm::userCreatedConfirmed(const bool isUserCreated){
    qDebug() << "User created status: "<< isUserCreated;

    if(isUserCreated){
        QMessageBox msgInfo(QMessageBox::Information, "Information", "\nWelcome to Personal Planner!");
        msgInfo.setStyleSheet("font-family: URW Gothic L");
        msgInfo.exec();
        resetUserInput();
        this->close();
    }else{
        QMessageBox msgWarn(QMessageBox::Warning, "Warning", "\nSomething went wrong... Please try again later.");
        msgWarn.setStyleSheet("font-family: URW Gothic L");
        msgWarn.exec();
    }
}

//Slots
/*! \brief This slot reads the user data from the RegistrationForm. If it is valid the user data will be created and saved in the database.
 * If not the user will be notified on the GUI that something is missing/wrong. */
void RegistrationForm::on_confirmBtn_clicked(){
    QString un;
    QString pass;
    QString firstname;
    QString lastname;
    QString email;

    QString style = "background-color: white; border: 2px solid red;";
    QString styleLb = "color:red;";

    bool isInvalid = false;

    if(ui->usernameTxt->text() == ""){
        ui->usernameTxt->setStyleSheet(style);
        ui->usernameTxt->setPlaceholderText("Username EMPTY!");
        isInvalid = true;
    }else{
        ui->usernameTxt->setStyleSheet("");
        un = ui->usernameTxt->text();
    }

    if(ui->passTxt->text() == ""){
        ui->passTxt->setStyleSheet(style);
        ui->passTxt->setPlaceholderText("Password EMPTY!");
        isInvalid = true;
    }else{
        ui->passTxt->setStyleSheet("");
        pass = ui->passTxt->text();
    }

    if(ui->firstnameTxt->text() == ""){
        ui->firstnameTxt->setStyleSheet(style);
        ui->firstnameTxt->setPlaceholderText("First Name EMPTY!");
        isInvalid = true;
    }else{
        ui->firstnameTxt->setStyleSheet("");
        firstname = ui->firstnameTxt->text();
    }

    if(ui->lastnameTxt->text() == ""){
        ui->lastnameTxt->setStyleSheet(style);
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        isInvalid = true;
    }else{
        ui->lastnameTxt->setStyleSheet("");
        lastname = ui->lastnameTxt->text();
    }

    if(ui->emailTxt->text() == ""){
        ui->emailTxt->setStyleSheet(style);
        ui->emailTxt->setPlaceholderText("E-mail EMPTY!");
        isInvalid = true;
    }else{
        ui->emailTxt->setStyleSheet("");
        email = ui->emailTxt->text();
    }

    if(isInvalid){
        ui->errLb->setStyleSheet(styleLb);
        ui->errLb->setEnabled(true);
        ui->errLb->setText("Please correct your mistakes.");
    }else{
        ui->errLb->setText("");
        ui->errLb->setEnabled(false);
        User t_user(un,pass,firstname,lastname,email);

        if (!p_userManager->checkUserExist(un))
            userCreatedConfirmed(p_userManager->create(t_user));
        else{
            QMessageBox msgWarn(QMessageBox::Warning, "Warning", "\nThe username '" + un + "' is already taken... \nPlease choose another username!");
            msgWarn.setStyleSheet("font-family: URW Gothic L");
            msgWarn.exec();
        }
    }
}


void RegistrationForm::on_cancelBtn_clicked(){
    resetUserInput();
    this->close();
}


void RegistrationForm::resetUserInput() {
    ui->usernameTxt->clear();
    ui->passTxt->clear();
    ui->firstnameTxt->clear();
    ui->lastnameTxt->clear();
    ui->emailTxt->clear();
    ui->errLb->clear();

    ui->usernameTxt->setPlaceholderText("");
    ui->passTxt->setPlaceholderText("");
    ui->firstnameTxt->setPlaceholderText("");
    ui->lastnameTxt->setPlaceholderText("");
    ui->emailTxt->setPlaceholderText("");

    ui->usernameTxt->setStyleSheet("");
    ui->passTxt->setStyleSheet("");
    ui->firstnameTxt->setStyleSheet("");
    ui->lastnameTxt->setStyleSheet("");
    ui->emailTxt->setStyleSheet("");
}
