#ifndef STATUSFORM_H
#define STATUSFORM_H

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
    void readStatusFromWindow();


private slots:
    void on_confirm_cancel_btn_accepted();

    void on_confirm_cancel_btn_rejected();

private:
    Ui::StatusForm *ui;
    QString status;
};

#endif // STATUSFORM_H
