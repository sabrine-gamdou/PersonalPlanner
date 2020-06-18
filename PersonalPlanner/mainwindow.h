#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userdaoimp.h"
#include "taskdaoimp.h"
#include "statusform.h"
#include "calendarmanager.h"

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QAbstractTableModel>
#include <QBrush>
#include <QtCore>
#include <QFileDialog>
#include <QImageReader>
#include <QPainter>

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
    bool readTaskFromMainWindow();
    void userUpdatedConfirmed(const bool t_userUpdated);
    void deleteTask();
    int setRepetitionIndex(QString repetitionString);
    void taskConfirmed(const bool taskUpdated);
    void resetTaskInput();
    void setStatusColor();
    void statusCounter();
    void loadImage(const QString& path);
    void synchronizeCalendar();


private slots:

    void on_deleteAccountBtn_clicked();

    void on_logoutBtn_clicked();

    void on_confirm_cancelBtnB_accepted();

    void on_confirm_cancelBtnB_rejected();

    void on_deleteBtn_clicked();

    void on_taskView_pressed();

    void on_editBtn_clicked();

    void on_saveChangesBtn_clicked();

    void on_statusBtn_clicked();

    void on_pictureBtn_clicked();

    void on_actionAbout_clicked();

    void on_actionHelp_clicked();

    void on_menuLogOut_clicked();

    void refreshData();
    void on_calendarWidget_clicked(const QDate &date);

private:


    Ui::MainWindow *ui;
    StatusForm sf;


    UserDaoImp m_userManager;
    TaskDaoImp m_taskManager;

    int mode;

    QString m_username;
    QString m_password;

    void logout();
};

#endif // MAINWINDOW_H
