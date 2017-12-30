#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class NeuronServer;
class NeuronPeer;
class Client;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    NeuronServer *serverManager;
    Client *client;

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

public slots:
    void on_serverManager_peerConnected(NeuronPeer *peer);
    void on_serverManager_peerDisconnected(NeuronPeer *peer);

};

#endif // MAINWINDOW_H
