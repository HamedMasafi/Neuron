#include "clientwindow.h"

#include "client.h"

#include "defines.h"

#include <NeuronClientHub>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent)
{

    hub = new NeuronClientHub(this);
    hub->setObjectName("hub");
//    hub->setAutoReconnect(true);
//    hub->setValidateToken(NEURON_VALIDATE_TOKEN);

    client = new Client(hub, this);
    client->setObjectName("client");

    hub->connectToHost("127.0.0.1", 8000);

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
    //client->getRandomNumber(spinBox->value());
}

void ClientWindow::on_pushButtonGetRandomNumber_clicked()
{
    client->getRandomNumber();
}
