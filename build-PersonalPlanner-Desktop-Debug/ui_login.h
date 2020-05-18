/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_15;
    QLabel *username_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_7;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_14;
    QLabel *firstname;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_13;
    QLabel *lastname;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_9;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_12;
    QLabel *birthday;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *address;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_11;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *password_2;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_12;
    QLineEdit *lineEdit_8;
    QPushButton *register_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *username;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *password;
    QLineEdit *lineEdit_2;
    QPushButton *login;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(637, 429);
        gridLayout_2 = new QGridLayout(Login);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        username_2 = new QLabel(Login);
        username_2->setObjectName(QStringLiteral("username_2"));

        horizontalLayout_15->addWidget(username_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        lineEdit_3 = new QLineEdit(Login);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        verticalLayout_7->addWidget(lineEdit_3);


        horizontalLayout_15->addLayout(verticalLayout_7);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        firstname = new QLabel(Login);
        firstname->setObjectName(QStringLiteral("firstname"));

        horizontalLayout_14->addWidget(firstname);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        lineEdit_4 = new QLineEdit(Login);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        verticalLayout_8->addWidget(lineEdit_4);


        horizontalLayout_14->addLayout(verticalLayout_8);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        lastname = new QLabel(Login);
        lastname->setObjectName(QStringLiteral("lastname"));

        horizontalLayout_13->addWidget(lastname);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        lineEdit_5 = new QLineEdit(Login);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        verticalLayout_9->addWidget(lineEdit_5);


        horizontalLayout_13->addLayout(verticalLayout_9);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        birthday = new QLabel(Login);
        birthday->setObjectName(QStringLiteral("birthday"));

        horizontalLayout_12->addWidget(birthday);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_4);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        lineEdit_6 = new QLineEdit(Login);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        verticalLayout_10->addWidget(lineEdit_6);


        horizontalLayout_12->addLayout(verticalLayout_10);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        address = new QLabel(Login);
        address->setObjectName(QStringLiteral("address"));

        horizontalLayout_11->addWidget(address);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        lineEdit_7 = new QLineEdit(Login);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        verticalLayout_11->addWidget(lineEdit_7);


        horizontalLayout_11->addLayout(verticalLayout_11);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        password_2 = new QLabel(Login);
        password_2->setObjectName(QStringLiteral("password_2"));

        horizontalLayout_10->addWidget(password_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        lineEdit_8 = new QLineEdit(Login);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        verticalLayout_12->addWidget(lineEdit_8);


        horizontalLayout_10->addLayout(verticalLayout_12);


        verticalLayout->addLayout(horizontalLayout_10);

        register_2 = new QPushButton(Login);
        register_2->setObjectName(QStringLiteral("register_2"));

        verticalLayout->addWidget(register_2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));

        verticalLayout_2->addLayout(horizontalLayout_16);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        username = new QLabel(Login);
        username->setObjectName(QStringLiteral("username"));

        horizontalLayout_5->addWidget(username);

        lineEdit = new QLineEdit(Login);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_5->addWidget(lineEdit);


        horizontalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        password = new QLabel(Login);
        password->setObjectName(QStringLiteral("password"));

        horizontalLayout_8->addWidget(password);

        lineEdit_2 = new QLineEdit(Login);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_8->addWidget(lineEdit_2);


        verticalLayout_4->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(verticalLayout_3);

        login = new QPushButton(Login);
        login->setObjectName(QStringLiteral("login"));

        verticalLayout_2->addWidget(login);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

        label = new QLabel(Login);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", Q_NULLPTR));
        username_2->setText(QApplication::translate("Login", "Username", Q_NULLPTR));
        firstname->setText(QApplication::translate("Login", "Firstname", Q_NULLPTR));
        lastname->setText(QApplication::translate("Login", "Lastname", Q_NULLPTR));
        birthday->setText(QApplication::translate("Login", "Birthday", Q_NULLPTR));
        address->setText(QApplication::translate("Login", "Address", Q_NULLPTR));
        password_2->setText(QApplication::translate("Login", "Password", Q_NULLPTR));
        register_2->setText(QApplication::translate("Login", "Register", Q_NULLPTR));
        username->setText(QApplication::translate("Login", "Username", Q_NULLPTR));
        password->setText(QApplication::translate("Login", "Password", Q_NULLPTR));
        login->setText(QApplication::translate("Login", "Login", Q_NULLPTR));
        label->setText(QApplication::translate("Login", "Image", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
