#include "clientwindow.h"

#include "user.h"
#include "server.h"

#include "defines.h"

#include <NeuronClientHub>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent), _resourceId(0)
{

    hub = new NeuronClientHub(this);
    hub->setObjectName("hub");
    hub->setAutoReconnect(true);
    hub->setValidateToken(NEURON_VALIDATE_TOKEN);

    server = new Server(hub, this);
    server->setObjectName("server");

    user = new User(hub, this);
    user->setObjectName("user");

    setupUi(this);
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

void ClientWindow::keyPressEvent(QKeyEvent *e)
{
    if(textEditMessage->hasFocus() && e->key() == Qt::Key_Return)
        on_pushButtonSend_clicked();
}

void ClientWindow::on_pushButtonLogin_clicked()
{
    hub->connectToHost(lineEditServer->text(), PORT, true);

    user->setUsername(lineEditUsername->text());
    labelUsername->setText(user->username());
    stackedWidget->setCurrentIndex(1);
}

void ClientWindow::on_pushButtonSend_clicked()
{
    user->sendMessageAsync(textEditMessage->toPlainText());
    textEditMessage->setPlainText("");
}

void ClientWindow::on_pushButtonChangeAvator_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Images (*.png *.xpm *.jpg)"));

    if(!fileName.isNull()){
        QPixmap pixmap(fileName);
        if(!pixmap.isNull()){
            user->setAvator(pixmap);
            labelAvator->setPixmap(pixmap);
        }
    }
}

void ClientWindow::on_server_userJoinedSignal(QString username)
{
    textEdit->append(QString("<span style=\" font-weight:600; color:#aa0000;\">%1 has joined to channel.</span>")
                     .arg(username));
}

void ClientWindow::on_server_userLeavedSignal(QString username)
{
    textEdit->append(QString("<span style=\" font-weight:600; color:#aa0000;\">%1 has leaved channel.</span>")
                     .arg(username));
}

void ClientWindow::on_server_imageSentSignal(QString username, QPixmap image)
{
    QString url = QString("res://image_%1.png").arg(_resourceId++);
    textEdit->document()->addResource(QTextDocument::ImageResource,
                                      QUrl(url),
                                      QVariant(image));

    textEdit->append("<b>" + username + "</b> Sent an image:<br /><img src=\"" + url + "\" />");
}

void ClientWindow::on_server_broadcastMessageSignal(QString message)
{
    QMessageBox::information(this, "Broadcast", message);
}

void ClientWindow::on_server_usersChanged(QVariantList users)
{
    listWidgetUsers->clear();
    foreach (QVariant v, users) {
        QVariantMap map = v.toMap();
        QListWidgetItem *item = new QListWidgetItem(map["username"].toString());

        if(map.contains("avator"))
            item->setIcon(QIcon(map["avator"].value<QPixmap>()));
        listWidgetUsers->addItem(item);
    }
}

void ClientWindow::on_hub_isConnectedChanged(bool isConnected)
{
    if(isConnected)
        statusBar()->showMessage("Connected");
    else
        statusBar()->showMessage("Disonnected");
}

void ClientWindow::on_user_messageRecivedSignal(QString username, QString message)
{
    textEdit->append(QString("<b><font color=%3>%1 :</font></b> %2")
                     .arg(username)
                     .arg(message)
                     .arg(username == user->username() ? "red" : "blue"));
}

void ClientWindow::imageSent()
{
    QMessageBox::information(this, "Send image", "Image was sent");
}

void ClientWindow::on_pushButtonSendImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));

    if(!fileName.isNull()){
        QPixmap pixmap(fileName);
        if(!pixmap.isNull())
            user->sendImage(pixmap, this, "imageSent");

            /*
             * if c++11 is enabled flowing code will be send image and show a messagebox
            user->sendImage(pixmap, [this](){
                QMessageBox::information(this, "Send image", "Image was sent");
            });
            */
    }
}
