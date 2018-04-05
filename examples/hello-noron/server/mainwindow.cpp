#include "mainwindow.h"

#include <Peer>
#include <Server>

#include "client.h"
#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    serverManager = new Server(PORT, this);
    serverManager->setObjectName("serverManager");
    serverManager->registerType<Client*>();
//    serverManager->setValidateToken(NEURON_VALIDATE_TOKEN);
    serverManager->setServerType(Server::SingleThread);

    setupUi(this);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_serverManager_peerConnected(Peer *peer)
{
    Client *client = qobject_cast<Client*>(peer);

    connect(client, &Client::getRandomNumberSignal, [=] {

    });

    listWidgetOnlineUsers->clear();
    foreach (Peer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<Client*>(p)->username());
}

void MainWindow::on_serverManager_peerDisconnected(Peer *peer)
{
    Q_UNUSED(peer);

    listWidgetOnlineUsers->clear();
    foreach (Peer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<Client*>(p)->username());
}
