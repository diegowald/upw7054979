#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int numClients = ui->txtNumberClients->text().toInt();
    clearClients();
    for (int i = 0; i < numClients; ++i)
    {
        MulticastReceiver *rec = new MulticastReceiver(i, this);
        _receivers.append(rec);
        connect(rec, &MulticastReceiver::multicastReceived, this, &MainWindow::on_multicastReceived);
    }
}

void MainWindow::clearClients()
{
    foreach (MulticastReceiver* rec, _receivers)
    {
        rec->deleteLater();
    }
    _receivers.clear();
}


void MainWindow::on_multicastReceived(int id, const QString &payload)
{
    QString txt = "%1: %2";
    ui->txtResult->setText(txt.arg(id).arg(payload));
}
