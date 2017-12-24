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
    void on_actionRefresh_triggered();

    void on_actionNew_User_triggered();

    void on_actionBlock_User_triggered();

    void on_actionUnblock_User_triggered();

    void on_actionE_xit_triggered();

    void httpFinished();
    void httpReadyRead();
    void sslErrors(QNetworkReply *, const QList<QSslError> &errors);

private:
    void performRequest(const QString &action, const QString &param);
    void responseList(const QString &response);
    void responseAdd(const QString &response);
    void responseBlock(const QString &response);
    void responseUnblock(const QString &response);

private:
    Ui::MainWindow *ui;


    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool httpRequestAborted;
    QString _commandInAction;
};

#endif // MAINWINDOW_H
