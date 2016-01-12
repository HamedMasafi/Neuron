#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class NoronServer;
class NoronPeer;
class Client;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    NoronServer *serverManager;
    Client *client;

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

public slots:
    void on_serverManager_peerConnected(NoronPeer *peer);
    void on_serverManager_peerDisconnected(NoronPeer *peer);

};

#endif // MAINWINDOW_H
