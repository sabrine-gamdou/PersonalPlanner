#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(379, 342);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    ui->passText->setEchoMode(QLineEdit::Password);
    ui->passText->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}


Login::~Login(){
    delete ui;
}

/*using const here crashes the program!*/
bool Login::login(QString &un, QString &pass){
    return this->m_userManager->checkLogin(un,pass);
}


void Login::initialize(QString &un, QString &pass){
    w.setUsername(un);
    w.setPassword(pass);
    w.getUserData();
    w.getTasks();
    w.show();
    this->close();
}

//Slots
void Login::on_loginBtn_clicked(){
    m_username = ui->usernameText->text();
    m_password = ui->passText->text();

    loggedIn = login(m_username,m_password);

    if(this->loggedIn){
        initialize(m_username,m_password);
    }
    else {
        ui->loginLabel->setText("Login failed: Invalid credentials!");
        ui->usernameText->setStyleSheet("border: 2px solid red");
        ui->passText->setStyleSheet("border: 2px solid red");
    }
}


void Login::on_registerBtn_clicked(){
    r.resetUserInput();
    r.show();
}


