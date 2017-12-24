#ifndef DLGNEWUSER_H
#define DLGNEWUSER_H

#include <QDialog>

namespace Ui {
class DlgNewUser;
}

class DlgNewUser : public QDialog
{
    Q_OBJECT

public:
    explicit DlgNewUser(QWidget *parent = 0);
    ~DlgNewUser();

    QString userName() const;
private:
    Ui::DlgNewUser *ui;
};

#endif // DLGNEWUSER_H
