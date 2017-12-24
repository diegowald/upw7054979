#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMessageBox>
#include <QNetworkReply>
#include "dlgnewuser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&qnam, &QNetworkAccessManager::sslErrors, this, &MainWindow::sslErrors);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRefresh_triggered()
{
    performRequest("list", ui->txtUser->text());
}

void MainWindow::on_actionNew_User_triggered()
{
    DlgNewUser dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        performRequest("add", dlg.userName());
    }
}

void MainWindow::on_actionBlock_User_triggered()
{
    if (ui->listUsers->selectedItems().count() > 0)
    {
        QString user = ui->listUsers->selectedItems()[0]->text();
        QStringList userSplitted = user.split(" ");
        performRequest("block", userSplitted[0]);
    }
}

void MainWindow::on_actionUnblock_User_triggered()
{
    if (ui->listUsers->selectedItems().count() > 0)
    {
        QString user = ui->listUsers->selectedItems()[0]->text();
        QStringList userSplitted = user.split(" ");
        performRequest("unblock", userSplitted[0]);
    }
}

void MainWindow::on_actionE_xit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::performRequest(const QString &action, const QString &param)
{
    _commandInAction = action;
    QString webAddress = ui->txtURL->text() + "/" + action + "/" + param;
    url = QUrl::fromUserInput(webAddress);
    if (!url.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(webAddress, url.errorString()));
        return;
    }

    httpRequestAborted = false;

    reply = qnam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);
}

void MainWindow::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    if (QMessageBox::warning(this, tr("SSL Errors"),
                             tr("One or more SSL errors has occurred:\n%1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
}

void MainWindow::httpFinished()
{
}

void MainWindow::httpReadyRead()
{
    QString response = reply->readAll();
    if (_commandInAction == "list")
    {
        responseList(response);
    }
    else if (_commandInAction == "add")
    {
        responseAdd(response);
    }
    else if (_commandInAction == "block")
    {
        responseBlock(response);
    }
    else if (_commandInAction == "unblock")
    {
        responseUnblock(response);
    }
}

void MainWindow::responseList(const QString &response)
{
    ui->listUsers->clear();
    QStringList list = response.split(";");
    foreach(QString user, list)
    {
        QStringList userSplitted = user.split(",");
        QString lbl = userSplitted[0];
        if (userSplitted[1] == "1")
        {
            lbl += " (blocked)";
        }
        ui->listUsers->addItem(lbl);
    }
}

void MainWindow::responseAdd(const QString &response)
{
    if (response == "OK")
        on_actionRefresh_triggered();
}

void MainWindow::responseBlock(const QString &response)
{
    if (response == "OK")
        on_actionRefresh_triggered();
}

void MainWindow::responseUnblock(const QString &response)
{
    if (response == "OK")
        on_actionRefresh_triggered();
}
