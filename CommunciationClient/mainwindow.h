#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();
    void httpFinished();
    void httpReadyRead();
    void sslErrors(QNetworkReply *, const QList<QSslError> &errors);

private:
    Ui::MainWindow *ui;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool httpRequestAborted;
};

#endif // MAINWINDOW_H
