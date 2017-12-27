#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../CommunciationClient/multicastreceiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void clearClients();
private slots:
    void on_pushButton_clicked();
    void on_multicastReceived(int id, const QString &payload);

private:
    Ui::MainWindow *ui;

    QList<MulticastReceiver*> _receivers;
};

#endif // MAINWINDOW_H
