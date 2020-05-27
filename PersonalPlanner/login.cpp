#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QFile>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

   // this->setStyleSheet("stylesheet.qss");
//    QFile File("stylesheet.qss");
//    File.open(QFile::ReadOnly);
//    QString StyleSheet = QLatin1String(File.readAll());

//    this->setStyleSheet(StyleSheet);

    ui->passText->setEchoMode(QLineEdit::Password);
    ui->passText->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

    QObject::connect(ui->loginBtn, &QPushButton::clicked, this, &Login::on_loginBtn_clicked);
    QObject::connect(ui->registerBtn, &QPushButton::clicked, this, &Login::on_registerBtn_clicked);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginBtn_clicked(){

    m_username = ui->usernameText->text();
    m_password = ui->passText->text();

    loggedIn = login(m_username,m_password);

    if(this->loggedIn)
    {
        //        this->username = ui->usernameText->text();
        //        this->password = ui->passText->text();

  //      QMessageBox::information(this, "Information", "You are logged in!");
        initialize(m_username,m_password);

    }
    else
    {
        //QMessageBox::warning(this, "Warning", "Login failed: Invalid credentials!");
        ui->loginLabel->setText("Login failed: Invalid credentials!");
        ui->usernameText->setStyleSheet("border: 1px solid red");
        ui->passText->setStyleSheet("border: 1px solid red");

    }
}

bool Login::login(QString un, QString pass){
    return this->m_userManager->checkLogin(un,pass);
}


void Login::on_registerBtn_clicked(){
    r.show();
    //this->setDisabled(true);
}


void Login::initialize(QString un, QString pass){


    w.show();
    this->close();
}
