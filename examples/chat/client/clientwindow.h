#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "ui_clientwindow.h"

#include <AbstractHub>
class User;
class ServerInstance;
namespace Neuron {
    class ClientHub;
}
class ClientWindow : public QMainWindow, private Ui::ClientWindow
{
    Q_OBJECT

    User *user;
    ServerInstance *server;
    Neuron::ClientHub *hub;
    qint32 _resourceId;

public:
    explicit ClientWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_hub_statusChanged(Neuron::AbstractHub::Status status);

    void on_server_userJoinedSignal(QString username);
    void on_server_userLeavedSignal(QString username);
    void on_server_imageSentSignal(QString username, QPixmap image);
    void on_server_broadcastMessageSignal(QString message);
    void on_server_usersChanged(QVariantList users);

    void on_user_messageRecivedSignal(QString username, QString message);

    void on_pushButtonLogin_clicked();
    void on_pushButtonSend_clicked();
    void on_pushButtonChangeAvator_clicked();
    void on_pushButtonSendImage_clicked();
};

#endif // CLIENTWINDOW_H
