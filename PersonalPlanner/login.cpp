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


bool Login::login(const QString &un, const QString &pass){
    return this->m_userManager->checkLogin(un,pass);
}

/* This method initializes the MainWindow with a username and password fetching all data and tasks related to the user. */
void Login::initialize(const QString &un, const QString &pass){
    w.setUsername(un);
    w.setPassword(pass);
    w.getUserData();
    w.getTasks();
    w.show();
    this->close();
}

//Slots

/* This method reads the user input and saves the value into global variables m_username and m_password and checks if the user exists.
 * if user exists -> the MainWindow will be initialized with the user data.
 * if not -> the user will be notified that his credentials are not valid. */
void Login::on_loginBtn_clicked(){
    m_username = ui->usernameText->text();
    m_password = ui->passText->text();

    loggedIn = login(m_username,m_password);

    if(this->loggedIn)
        initialize(m_username,m_password);
    else {
        ui->loginLabel->setText("Login failed: Invalid credentials!");
        ui->usernameText->setStyleSheet("background-color: white; border: 2px solid red");
        ui->passText->setStyleSheet("background-color: white; border: 2px solid red");
    }
}


void Login::on_registerBtn_clicked(){
    r.resetUserInput();
    r.show();
}


