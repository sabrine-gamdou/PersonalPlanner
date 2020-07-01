#ifndef STATUSFORM_H
#define STATUSFORM_H

#include "task.h"
#include "taskdaoimp.h"
#include "tasklistmodel.h"

#include <QDialog>

namespace Ui {
class StatusForm;
}

class StatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit StatusForm(QWidget *parent = 0);
    ~StatusForm();

    Task *readStatusFromWindow();
    void giveTask(const Task &task);
    void setStatus(const QString &value);
    void initializeStatusForm();

private slots:
    void on_confirm_cancel_btn_accepted();
    void on_confirm_cancel_btn_rejected();

signals:
    void refreshGUI();

private:
    Ui::StatusForm *ui;

    QString m_status;
    TaskDaoImp m_taskManager;
    Task m_task;
    TaskListModel m_taskModel;
};

#endif // STATUSFORM_H
