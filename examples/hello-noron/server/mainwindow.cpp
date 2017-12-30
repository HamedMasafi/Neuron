#include "mainwindow.h"

#include <NeuronPeer>
#include <NeuronServer>

#include "client.h"
#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    serverManager = new NeuronServer(PORT, this);
    serverManager->setObjectName("serverManager");
    serverManager->registerType<Client*>();
//    serverManager->setValidateToken(NEURON_VALIDATE_TOKEN);
    serverManager->setServerType(NeuronServer::SingleThread);

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

void MainWindow::on_serverManager_peerConnected(NeuronPeer *peer)
{
    Client *client = qobject_cast<Client*>(peer);

    connect(client, &Client::getRandomNumberSignal, [=] {

    });

    listWidgetOnlineUsers->clear();
    foreach (NeuronPeer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<Client*>(p)->username());
}

void MainWindow::on_serverManager_peerDisconnected(NeuronPeer *peer)
{
    Q_UNUSED(peer);

    listWidgetOnlineUsers->clear();
    foreach (NeuronPeer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<Client*>(p)->username());
}
