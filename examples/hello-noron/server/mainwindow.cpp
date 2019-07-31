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
    serverManager->setObjectName(QString::fromUtf8("serverManager"));
    serverManager->registerType<AbstractClient*>();
    serverManager->setEncoder(new Neuron::SimpleTokenValidator(NEURON_VALIDATE_TOKEN));
    serverManager->setServerType(Neuron::Server::MultiThread);

    serverManager->startServer(PORT);

    connect(serverManager, &Neuron::Server::peerConnected, this, &MainWindow::on_serverManager_peerConnected);
    connect(serverManager, &Neuron::Server::peerDisconnected, this, &MainWindow::on_serverManager_peerDisconnected);
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

    QListWidgetItem *item = new QListWidgetItem(listWidgetOnlineUsers);
    item->setData(Qt::EditRole, QVariant::fromValue(client));
    item->setText(client->username());

    connect(client, &AbstractClient::getRandomNumberSignal, [=] (int &r){
        r = 4;
    });
    connect(client, &AbstractClient::usernameChanged, [item] (QString username){
        item->setText(username);
    });

//    listWidgetOnlineUsers->addItem(item);
//    listWidgetOnlineUsers->clear();
//    foreach (Neuron::Peer *p, serverManager->peers())
//        listWidgetOnlineUsers->addItem(qobject_cast<AbstractClient*>(p)->username());
}

void MainWindow::on_serverManager_peerDisconnected(Neuron::Peer *peer)
{
    qDebug() << Q_FUNC_INFO;
    Q_UNUSED(peer);

    AbstractClient *client = qobject_cast<AbstractClient*>(peer);
    QVariant v = QVariant::fromValue(client);

    for (int i = 0; i < listWidgetOnlineUsers->count(); ++i) {
        if (listWidgetOnlineUsers->item(i)->data(Qt::EditRole) == v) {
            listWidgetOnlineUsers->takeItem(i);
            break;
        }
    }
//    listWidgetOnlineUsers->clear();
//    foreach (Neuron::Peer *p, serverManager->peers())
//        listWidgetOnlineUsers->addItem(qobject_cast<AbstractClient*>(p)->username());
}

void MainWindow::on_pushButtonSendBroadcast_clicked()
{
//    foreach (Neuron::Peer *p, serverManager->peers())
//qobject_cast<AbstractClient*>(p)->
}
