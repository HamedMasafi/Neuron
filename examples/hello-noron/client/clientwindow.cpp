#include "clientwindow.h"

#include "abstractclient.h"

#include "defines.h"

#include <ClientHub>
#include <SimpleTokenValidator>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent)
{

    hub = new Neuron::ClientHub(this);
    hub->setObjectName("hub");
//    hub->setAutoReconnect(true);
    hub->setEncoder(new Neuron::SimpleTokenValidator(NEURON_VALIDATE_TOKEN));

    client = new AbstractClient(hub, this);
    client->setObjectName("client");

    hub->connectToHost("localhost", PORT, true);

    setupUi(this);
}

void ClientWindow::on_client_getRandomNumberSignal(int returnValue)
{
    labelResult->setText(QString("Result is: %1")
                         .arg(returnValue));
}

void ClientWindow::on_client_getRandomNumberSignal(int timeout, int returnValue)
{
    labelResult->setText(QString("Result is: %1 (after %2 ms)")
                         .arg(returnValue)
                         .arg(timeout));
}

void ClientWindow::changeEvent(QEvent *e)
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

void ClientWindow::on_hub_isConnectedChanged(bool isConnected)
{
    if(isConnected)
        statusBar()->showMessage("Connected");
    else
        statusBar()->showMessage("Disonnected");
}


void ClientWindow::on_pushButtonGetRandomNumberWithTimeout_clicked()
{
    client->getRandomNumber()->then([=](int n){
        labelResult->setText(QString::number(n));
    });
}

void ClientWindow::on_pushButtonGetRandomNumber_clicked()
{
    client->getRandomNumber()->wait();
}
