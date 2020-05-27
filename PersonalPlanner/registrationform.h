#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include "userdaoimp.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = 0);
    ~RegistrationForm();
    void on_confirmBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::RegistrationForm *ui;
    UserDaoImp* m_userManager;
    void userCreatedConfirmed(bool t_userCreated);
};

#endif // REGISTRATIONFORM_H

