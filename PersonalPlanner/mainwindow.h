#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userdaoimp.h"
#include "taskdaoimp.h"

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QAbstractTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    void getTasks();
    void getUserData();
    void editInfoCheckBox_checked(const bool checked);
    void menuLogOut_clicked();
    void readTaskFromMainWindow();
    void userUpdatedConfirmed(const bool t_userUpdated);

private slots:

    void on_deleteAccountBtn_clicked();
    void on_logoutBtn_clicked();


    void on_confirm_cancelBtnB_accepted();

    void on_confirm_cancelBtnB_rejected();

    void on_deleteBtn_clicked();

    void on_taskView_pressed();

    void on_editBtn_clicked();

    void on_saveChangesBtn_clicked();

private:
    Ui::MainWindow *ui;


    UserDaoImp m_userManager;
    TaskDaoImp m_taskManager;

    QString m_username;
    QString m_password;

    void logout();
};

#endif // MAINWINDOW_H
