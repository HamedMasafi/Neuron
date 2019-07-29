#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "ui_clientwindow.h"

namespace Neuron {
    class ClientHub;
}
class AbstractClient;
class ClientWindow : public QMainWindow, private Ui::ClientWindow
{
    Q_OBJECT

    AbstractClient *client;
    Neuron::ClientHub *hub;

public:
    explicit ClientWindow(QWidget *parent = 0);
    void changeEvent(QEvent *e);

private slots:
    void on_client_getRandomNumberSignal(int timeout, int returnValue);
    void on_client_getRandomNumberSignal(int returnValue);

    void on_hub_isConnectedChanged(bool isConnected);

    void on_pushButtonGetRandomNumberWithTimeout_clicked();
    void on_pushButtonGetRandomNumber_clicked();
};

#endif // CLIENTWINDOW_H
