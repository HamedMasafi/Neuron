#include "mainwindow.h"

#include <NoronPeer>
#include <NoronServer>

#include "client.h"
#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    serverManager = new NoronServer(PORT, this);
    serverManager->setObjectName("serverManager");
    serverManager->registerType<Client*>();
//    serverManager->setValidateToken(NORON_VALIDATE_TOKEN);
    serverManager->setServerType(NoronServer::SingleThread);

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

void MainWindow::on_serverManager_peerConnected(NoronPeer *peer)
{
    Client *client = qobject_cast<Client*>(peer);

    connect(client, &Client::getRandomNumberSignal, [=] {

    });

    listWidgetOnlineUsers->clear();
    foreach (NoronPeer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<Client*>(p)->username());
}

void MainWindow::on_serverManager_peerDisconnected(NoronPeer *peer)
{
    Q_UNUSED(peer);

    listWidgetOnlineUsers->clear();
    foreach (NoronPeer *p, serverManager->peers())
        listWidgetOnlineUsers->addItem(qobject_cast<Client*>(p)->username());
}
