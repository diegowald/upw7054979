#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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
        QString url = "https://portchecker.co/check";
        HttpRequestInput req(url, "POST");

        req.add_var("target_ip", ui->txtURL->text());
        req.add_var("port", ui->txtPort->text());

        HttpRequestWorker *worker = new HttpRequestWorker(this);
        connect(worker, &HttpRequestWorker::on_execution_finished, this, &MainWindow::on_execution_finished);

        worker->execute(&req);
}

void MainWindow::on_execution_finished(HttpRequestWorker *worker)
{
    QString msg;
    if (worker->error_type == QNetworkReply::NoError)
    {
        // communication was successful
        msg = worker->response;
    }
    else
    {
        // an error occurred
        msg = worker->error_str;
    }
    qDebug() << worker->error_type;
    qDebug() << msg;
    ui->lblResult->setText(msg);
    worker->deleteLater();

}
