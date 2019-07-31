#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <ClientHub>
#include <Peer>

#include <SimpleTokenValidator>
#include "user.h"
#include "serverinstance.h"
#include "defines.h"
#include "pixmap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

//    qRegisterMetaType<Neuron::SimpleTokenValidator>();
//    qRegisterMetaType<Neuron::SimpleTokenValidator*>();
//    qmlRegisterType<Neuron::SimpleTokenValidator>("Tooj.RPC", 1, 0, "SimpleTokenValidator");
//    qmlRegisterType<Neuron::ClientHub>("Tooj.RPC", 1, 0, "Hub");
//    qmlRegisterType<Neuron::Peer>("Tooj.RPC", 1, 0, "Peer");
//    qmlRegisterType<User>("Tooj.RPC", 1, 0, "User");
//    qmlRegisterType<ServerInstance>("Tooj.RPC", 1, 0, "ServerInstance");
    qmlRegisterUncreatableType<Neuron::AbstractCall>("Tooj.RPC", 1, 0, "Call", "");
    qmlRegisterType<Pixmap>("Tooj.RPC", 1, 0, "Pixmap");

    auto hub = new Neuron::ClientHub;
    hub->setObjectName("hub");
    hub->setAutoReconnect(true);
    hub->setEncoder(new Neuron::SimpleTokenValidator(NEURON_VALIDATE_TOKEN, hub));
    hub->setPort(PORT);

    auto server = new ServerInstance(hub);
    server->setObjectName("server");

    auto user = new User(hub);
    user->setObjectName("user");

    engine.rootContext()->setContextProperty("User", user);
    engine.rootContext()->setContextProperty("Hub", hub);
    engine.rootContext()->setContextProperty("Server", server);
    engine.rootContext()->setContextProperty("RPC_TOKEN", QVariant(NEURON_VALIDATE_TOKEN));
    engine.rootContext()->setContextProperty("PORT", QVariant(PORT));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
