#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class NeuronServer;
class NeuronPeer;
class Server;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    NeuronServer *serverManager;
    Server *server;
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void populatePeersList();

public slots:
    void on_serverManager_peerConnected(NeuronPeer *peer);
    void on_serverManager_peerDisconnected(NeuronPeer *peer);

    void user_sendImageSignal(QPixmap image);
    void user_sendMessageSignal(QString message);
    void user_usernameChanged();

private slots:
    void on_pushButtonSendBroadcast_clicked();
};

#endif // MAINWINDOW_H
