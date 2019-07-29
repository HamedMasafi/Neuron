#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

namespace Neuron {
    class Server;
    class Peer;
}

class AbstractClient;
class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    Neuron::Server *serverManager;
    AbstractClient *client;

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *e);

public slots:
    void on_serverManager_peerConnected(Neuron::Peer *peer);
    void on_serverManager_peerDisconnected(Neuron::Peer *peer);

};

#endif // MAINWINDOW_H
