#include "login.h"
#include "ui_login.h"

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
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    ui->passText->setEchoMode(QLineEdit::Password);
    ui->passText->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginBtn_clicked(){

    m_username = ui->usernameText->text();
    m_password = ui->passText->text();

    loggedIn = login(m_username,m_password);

    if(this->loggedIn){
        initialize(m_username,m_password);
    }
    else {
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


void Login::initialize(const QString & un, const QString &pass) {
    w.setUsername(un);
    w.setPassword(pass);
    w.getUserData();
    w.getTasks();
    w.show();
    this->close();
}
