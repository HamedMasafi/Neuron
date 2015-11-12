#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class RpcServer;
class RpcPeer;
class Server;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    RpcServer *serverManager;
    Server *server;
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void populatePeersList();

public slots:
    void on_serverManager_peerConnected(RpcPeer *peer);
    void on_serverManager_peerDisconnected(RpcPeer *peer);

    void user_sendImageSignal(QPixmap image);
    void user_sendMessageSignal(QString message);
    void user_usernameChanged();

private slots:
    void on_pushButtonSendBroadcast_clicked();
};

#endif // MAINWINDOW_H
