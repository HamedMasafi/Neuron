#include "mainwindow.h"

#include <Peer>
#include <Server>
#include <SimpleTokenValidator>

#include "abstractclient.h"
#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qRegisterMetaType<AbstractClient*>();
    serverManager = new Neuron::Server(this);
    serverManager->setObjectName("serverManager");
    serverManager->registerType<AbstractClient*>();
    serverManager->setEncoder(new Neuron::SimpleTokenValidator(NEURON_VALIDATE_TOKEN));
    serverManager->setServerType(Neuron::Server::MultiThread);

    serverManager->startServer(PORT);

    connect(serverManager, &Neuron::Server::peerConnected, this, &MainWindow::on_serverManager_peerConnected);
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

void MainWindow::on_serverManager_peerConnected(Neuron::Peer *peer)
{
    qDebug() << Q_FUNC_INFO;
    AbstractClient *client = qobject_cast<AbstractClient*>(peer);

    connect(client, &AbstractClient::getRandomNumberSignal, [=] (int &r){
        r = 4;
    });

    listWidgetOnlineUsers->clear();
    foreach (Neuron::Peer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<AbstractClient*>(p)->username());
}

void MainWindow::on_serverManager_peerDisconnected(Neuron::Peer *peer)
{
    qDebug() << Q_FUNC_INFO;
    Q_UNUSED(peer);

    listWidgetOnlineUsers->clear();
    foreach (Neuron::Peer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<AbstractClient*>(p)->username());
}
