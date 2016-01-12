#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "ui_clientwindow.h"

class Client;
class NoronClientHub;
class ClientWindow : public QMainWindow, private Ui::ClientWindow
{
    Q_OBJECT

    Client *client;
    NoronClientHub *hub;

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
