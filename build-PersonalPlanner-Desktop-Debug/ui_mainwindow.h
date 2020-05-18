/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Delete;
    QAction *actionAbout;
    QAction *actionHelp;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *Aufgabe;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_17;
    QLineEdit *lineEdit_7;
    QSpinBox *spinBox;
    QDateTimeEdit *dateTimeEdit;
    QComboBox *comboBox;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pushButton_11;
    QPushButton *pushButton_15;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_16;
    QDialogButtonBox *buttonBox;
    QWidget *tab_5;
    QTableWidget *tableWidget;
    QWidget *tab_6;
    QWidget *tab_3;
    QProgressBar *progressBar_2;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QVBoxLayout *verticalLayout_5;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QPushButton *pushButton_10;
    QWidget *tab_2;
    QLabel *label;
    QCommandLinkButton *commandLinkButton;
    QCommandLinkButton *commandLinkButton_2;
    QCheckBox *checkBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_6;
    QCalendarWidget *calendarWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuLogOut;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(873, 532);
        actionAdd_Delete = new QAction(MainWindow);
        actionAdd_Delete->setObjectName(QStringLiteral("actionAdd_Delete"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        Aufgabe = new QWidget();
        Aufgabe->setObjectName(QStringLiteral("Aufgabe"));
        tabWidget_2 = new QTabWidget(Aufgabe);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(20, 20, 341, 331));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_6 = new QGridLayout(tab_4);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        lineEdit_6 = new QLineEdit(tab_4);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        verticalLayout_8->addWidget(lineEdit_6);

        pushButton_17 = new QPushButton(tab_4);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));

        verticalLayout_8->addWidget(pushButton_17);

        lineEdit_7 = new QLineEdit(tab_4);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        verticalLayout_8->addWidget(lineEdit_7);

        spinBox = new QSpinBox(tab_4);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(5);
        spinBox->setValue(1);

        verticalLayout_8->addWidget(spinBox);

        dateTimeEdit = new QDateTimeEdit(tab_4);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));

        verticalLayout_8->addWidget(dateTimeEdit);

        comboBox = new QComboBox(tab_4);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_8->addWidget(comboBox);


        gridLayout_6->addLayout(verticalLayout_8, 0, 1, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        pushButton_11 = new QPushButton(tab_4);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        verticalLayout_6->addWidget(pushButton_11);

        pushButton_15 = new QPushButton(tab_4);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));

        verticalLayout_6->addWidget(pushButton_15);

        pushButton_12 = new QPushButton(tab_4);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));

        verticalLayout_6->addWidget(pushButton_12);

        pushButton_13 = new QPushButton(tab_4);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        verticalLayout_6->addWidget(pushButton_13);

        pushButton_14 = new QPushButton(tab_4);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        verticalLayout_6->addWidget(pushButton_14);

        pushButton_16 = new QPushButton(tab_4);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));

        verticalLayout_6->addWidget(pushButton_16);


        horizontalLayout_3->addLayout(verticalLayout_6);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(tab_4);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout_6->addWidget(buttonBox, 1, 1, 1, 1);

        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tableWidget = new QTableWidget(tab_5);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(15, 11, 311, 271));
        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tabWidget_2->addTab(tab_6, QString());
        tabWidget->addTab(Aufgabe, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        progressBar_2 = new QProgressBar(tab_3);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setGeometry(QRect(0, 320, 371, 23));
        progressBar_2->setValue(24);
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 300, 67, 17));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 20, 101, 71));
        gridLayoutWidget_3 = new QWidget(tab_3);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 90, 361, 131));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_7 = new QPushButton(gridLayoutWidget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_4->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(gridLayoutWidget_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout_4->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(gridLayoutWidget_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        verticalLayout_4->addWidget(pushButton_9);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        lcdNumber = new QLCDNumber(gridLayoutWidget_3);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setDigitCount(5);

        verticalLayout_5->addWidget(lcdNumber);

        lcdNumber_2 = new QLCDNumber(gridLayoutWidget_3);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));

        verticalLayout_5->addWidget(lcdNumber_2);

        lcdNumber_3 = new QLCDNumber(gridLayoutWidget_3);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));

        verticalLayout_5->addWidget(lcdNumber_3);


        horizontalLayout->addLayout(verticalLayout_5);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        pushButton_10 = new QPushButton(tab_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(10, 240, 174, 25));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 111, 31));
        commandLinkButton = new QCommandLinkButton(tab_2);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(240, 330, 81, 41));
        commandLinkButton_2 = new QCommandLinkButton(tab_2);
        commandLinkButton_2->setObjectName(QStringLiteral("commandLinkButton_2"));
        commandLinkButton_2->setGeometry(QRect(240, 290, 121, 41));
        checkBox = new QCheckBox(tab_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(240, 10, 131, 23));
        gridLayoutWidget_2 = new QWidget(tab_2);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(19, 89, 331, 201));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton = new QPushButton(gridLayoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(gridLayoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(gridLayoutWidget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(gridLayoutWidget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_5 = new QPushButton(gridLayoutWidget_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);


        horizontalLayout_2->addLayout(verticalLayout_2);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lineEdit_2 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout_3->addWidget(lineEdit_2);

        lineEdit = new QLineEdit(gridLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_3->addWidget(lineEdit);

        lineEdit_3 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        verticalLayout_3->addWidget(lineEdit_3);

        lineEdit_5 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        verticalLayout_3->addWidget(lineEdit_5);

        lineEdit_4 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        verticalLayout_3->addWidget(lineEdit_4);


        gridLayout_3->addLayout(verticalLayout_3, 0, 1, 1, 1);

        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(20, 300, 101, 25));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));

        gridLayout->addWidget(calendarWidget, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout_2->addLayout(verticalLayout, 1, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout_2->addWidget(progressBar, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 873, 22));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        menuLogOut = new QMenu(menuBar);
        menuLogOut->setObjectName(QStringLiteral("menuLogOut"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuLogOut->menuAction());
        menuMenu->addAction(actionAdd_Delete);
        menuMenu->addAction(actionAbout);
        menuMenu->addAction(actionHelp);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionAdd_Delete->setText(QApplication::translate("MainWindow", "Add / Delete", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tasks", Q_NULLPTR));
        pushButton_17->setText(QApplication::translate("MainWindow", "Pick Icon", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Hour", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Day", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Week", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Month", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Year", Q_NULLPTR)
        );
        pushButton_11->setText(QApplication::translate("MainWindow", "Title", Q_NULLPTR));
        pushButton_15->setText(QApplication::translate("MainWindow", "Icon", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("MainWindow", "Description", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("MainWindow", "Importance", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("MainWindow", "Duration", Q_NULLPTR));
        pushButton_16->setText(QApplication::translate("MainWindow", "Repeat Task every...", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "Add Task", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Title", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Date", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "Delete Task", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "Edit Task", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Aufgabe), QApplication::translate("MainWindow", "Add / Delete", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Level: X", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Score Picture", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "Completed Tasks", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "Failed Tasks", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "Tasks in progress", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindow", "Statistic", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Score", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Profile Picture", Q_NULLPTR));
        commandLinkButton->setText(QApplication::translate("MainWindow", "LogOut", Q_NULLPTR));
        commandLinkButton_2->setText(QApplication::translate("MainWindow", "Delete Account", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "Edit Information", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Firstname", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Lastname", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Birthday", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Address", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "E-Mail", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "Save changes", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Account", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Weekly Archivements: ", Q_NULLPTR));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
        menuLogOut->setTitle(QApplication::translate("MainWindow", "LogOut", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
