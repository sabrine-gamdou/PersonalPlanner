#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->passText->setEchoMode(QLineEdit::Password);
    ui->passText->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

    QObject::connect(ui->login, &QPushButton::clicked, this, &Login::on_login_clicked);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked(){

    loggedIn = login(ui->usernameText->text(), ui->passText->text());

    if(this->loggedIn)
    {
        //        this->username = ui->usernameText->text();
        //        this->password = ui->passText->text();

        QMessageBox::information(this, "Information", "You are logged in!");
       // ui->usernameText->setText("checked");
        // ui->loginLabel->setText("");
        //ui->winStack->setCurrentIndex(2);
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Login failed: Invalid credentials!");
        // ui->loginLabel->setText("Login failed: Invalid credentials!");
    }
}

bool Login::login(QString u, QString p){
    //ui->adminButton->setVisible(false);

    //    bool exists = false;



    //    if (checkQuery.exec())
    //    {
    //        if (checkQuery.next())
    //        {
    //            exists = true;
    //        }
    //    }

    return this->m_userManager->checkLogin(u,p);
}
