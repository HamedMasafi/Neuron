#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "ui_clientwindow.h"

class User;
class ClientWindow : public QMainWindow, private Ui::ClientWindow
{
    Q_OBJECT

    User *user;
    qint32 _resourceId;

public:
    explicit ClientWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_hub_isConnectedChanged(bool isConnected);

    void on_server_userJoinedHandle(QString username);
    void on_server_imageSentHandle(QString username, QPixmap image);
    void on_server_broadcastMessageHandle(QString message);

    void on_user_messageRecivedHandle(QString username, QString message);
    void on_user_roomMessageHandle(QString message);

    void imageSent();

    void on_pushButtonLogin_clicked();
    void on_pushButtonSend_clicked();
    void on_pushButtonChangeAvator_clicked();
    void on_pushButtonSendImage_clicked();
};

#endif // CLIENTWINDOW_H
