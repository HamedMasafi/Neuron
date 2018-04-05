#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class Server;
class Peer;
class Client;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    Server *serverManager;
    Client *client;

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

public slots:
    void on_serverManager_peerConnected(Peer *peer);
    void on_serverManager_peerDisconnected(Peer *peer);

};

#endif // MAINWINDOW_H
