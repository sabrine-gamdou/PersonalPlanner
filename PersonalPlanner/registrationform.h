#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include "userdaoimp.h"

#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = 0);
    ~RegistrationForm();
    void resetUserInput();

private slots:
    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::RegistrationForm *ui;
    UserDaoImp *m_userManager;
    void userCreatedConfirmed(const bool isUserCreated);

};

#endif // REGISTRATIONFORM_H

