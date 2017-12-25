#include "dlgnewuser.h"
#include "ui_dlgnewuser.h"

DlgNewUser::DlgNewUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgNewUser)
{
    ui->setupUi(this);
}

DlgNewUser::~DlgNewUser()
{
    delete ui;
}

QString DlgNewUser::userName() const
{
    return ui->txtUser->text();
}

void DlgNewUser::on_buttonBox_accepted()
{

    close();
}
