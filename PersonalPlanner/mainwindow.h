#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userdaoimp.h"
#include "taskdaoimp.h"
#include "statusform.h"
#include "calendarmanager.h"
#include "helpform.h"
#include "aboutform.h"
#include "statisticsform.h"

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QAbstractTableModel>
#include <QFileDialog>
#include <QImageReader>
#include <QByteArray>

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
    bool titleExists(const QString title);
    Task readTaskData();
    bool readTaskAndCheckIfValid();
    void userUpdatedConfirmed(const bool isUserUpdated);
    void deleteTask();
    int setRepetitionIndex(QString repetitionString);
    void setRepetitionDuration(const QDate &date, Task task);
    void taskConfirmed(const bool isTaskUpdated);
    void resetTaskInput();
    void statusCounter();
    int countScore(int completed, int failed);
    void setProgressbar();
    void resetButtons();
    void loadImage(const QString &path);
    void synchronizeCalendar();
    QByteArray convertImageToByteArray(QImage &img);
    void convertByteArrayToImage(QByteArray &arr);
    void closeAllWindows();

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
    void on_actionAboutClicked();
    void on_actionHelpClicked();
    void on_actionLogoutClicked();
    void refreshData();
    void on_calendarWidget_clicked(const QDate &date);
    void on_statisticBtn_clicked();
    void on_deleteAllBtn_clicked();

private:
    Ui::MainWindow *ui;
    StatusForm m_sf;
    HelpForm m_hf;
    AboutForm m_af;
    StatisticsForm m_ssf;

    UserDaoImp m_userManager;
    TaskDaoImp m_taskManager;

    int m_mode;
    int m_width;
    int m_height;
    int m_score;

    QString m_username;
    QString m_password;

    void logout();
};

#endif // MAINWINDOW_H
