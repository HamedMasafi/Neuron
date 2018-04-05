#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class Server;
class Peer;
class Server;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    Server *serverManager;
    Server *server;
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void populatePeersList();

public slots:
    void on_serverManager_peerConnected(Peer *peer);
    void on_serverManager_peerDisconnected(Peer *peer);

    void user_sendImageSignal(QPixmap image);
    void user_sendMessageSignal(QString message);
    void user_usernameChanged();

private slots:
    void on_pushButtonSendBroadcast_clicked();
};

#endif // MAINWINDOW_H
