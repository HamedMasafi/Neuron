#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <NeuronClientHub>
#include <NeuronPeer>

#include "user.h"
#include "server.h"
#include "defines.h"
#include "pixmap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<NeuronClientHub>("Tooj.RPC", 1, 0, "Hub");
    qmlRegisterType<NeuronPeer>("Tooj.RPC", 1, 0, "Peer");
    qmlRegisterType<User>("Tooj.RPC", 1, 0, "User");
    qmlRegisterType<Server>("Tooj.RPC", 1, 0, "Server");
    qmlRegisterType<Pixmap>("Tooj.RPC", 1, 0, "Pixmap");

    engine.rootContext()->setContextProperty("RPC_TOKEN", QVariant(NEURON_VALIDATE_TOKEN));
    engine.rootContext()->setContextProperty("PORT", QVariant(PORT));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
