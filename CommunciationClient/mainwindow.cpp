#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QNetworkReply>
#include <QTimer>

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

void MainWindow::on_btnConnect_clicked()
{
    QString webAddress = ui->txtURL->text() + "/content/" + ui->txtUser->text();
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
/*    QFileInfo fi;
    if (file) {
        fi.setFile(file->fileName());
        file->close();
        delete file;
        file = nullptr;
    }

    if (httpRequestAborted) {
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    if (reply->error()) {
        QFile::remove(fi.absoluteFilePath());
        statusLabel->setText(tr("Download failed:\n%1.").arg(reply->errorString()));
        downloadButton->setEnabled(true);
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = nullptr;

    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(this, tr("Redirect"),
                                  tr("Redirect to %1 ?").arg(redirectedUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
            QFile::remove(fi.absoluteFilePath());
            downloadButton->setEnabled(true);
            statusLabel->setText(tr("Download failed:\nRedirect rejected."));
            return;
        }
        file = openFileForWrite(fi.absoluteFilePath());
        if (!file) {
            downloadButton->setEnabled(true);
            return;
        }
        startRequest(redirectedUrl);
        return;
    }

    statusLabel->setText(tr("Downloaded %1 bytes to %2\nin\n%3")
                         .arg(fi.size()).arg(fi.fileName(), QDir::toNativeSeparators(fi.absolutePath())));
    if (launchCheckBox->isChecked())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absoluteFilePath()));
    downloadButton->setEnabled(true);    */
}

void MainWindow::httpReadyRead()
{
    ui->txtResponse->setText(reply->readAll());
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    /*if (file)
        file->write(reply->readAll());*/

    QTimer::singleShot(1000, this, SLOT(on_btnConnect_clicked()));
}
