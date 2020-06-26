#ifndef STATUSFORM_H
#define STATUSFORM_H

#include "task.h"
#include "taskdaoimp.h"
#include "tasklistmodel.h"
#include <QDialog>
#include <QString>

namespace Ui {
class StatusForm;
}

class StatusForm : public QDialog
{
    Q_OBJECT

public:
    explicit StatusForm(QWidget *parent = 0);
    ~StatusForm();

    QString getStatus() const;
    void setStatus(const QString &value);
    Task *readStatusFromWindow();
    void giveTask(Task &task);

private slots:
    void on_confirm_cancel_btn_accepted();
    void on_confirm_cancel_btn_rejected();

signals:
    void refreshGUI();

private:
    Ui::StatusForm *ui;

    QString status;
    TaskDaoImp m_taskDao;
    Task m_task;
    TaskListModel m_taskModel;
};

#endif // STATUSFORM_H
