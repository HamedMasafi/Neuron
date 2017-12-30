# Neuron

Qt Remote object sharing

This tool implements remote object sharing (Object Oriented RPC) in Qt. From a technical point of view it can compare with Java RMI or similar technologies. Neuron has an advanced signaling mechanism. A property change on a peer (server or client) will immediately signal a change on other peers. It can transfer every QVariant type (even QPixmap and complex types). 

The Neuron project is a framework that performs remote method invocation on client/server shared objects, the object-oriented equivalent of remote procedure calls (RPC). With support for direct transfer of serialized c++ types and QObject based objects.

## Features
- Simple to use
- Client & Server peers and classes generator tool
- Asynchronous and synchronous function calls
   - QML callback function
   - C++11 std::function callback
   - QMetaMethod callback
   - const *char for invoking on result
   - Asynchronous method call without response checking
   - Synchronous method call (with UI freez)
- Remote event emit
- Support all of QMetaType (include all classes delivered from QObject)
- Simple error checking
- Token based request validation
- Single thread and multi thread server

## Documentation
There no document right now. Have a look at examples for an example on how to get started. The other examples in the examples folder cover the major features of the library.

## How to use
#### Step1: Use peer-generator
First create a template document put your peer class code like that:

```c++
class User : public NeuronPeer {
	Q_PROPERTY(quint32 id)
	Q_PROPERTY(QString displayName)
	Q_PROPERTY(QImage avatar)
	
	void sendMessage(QString message);
};
```
Use peer-generator tool for creating User.cpp & User.h
```bash
    $peer-generator template.h
```
#### Step 2: Write codes

##### Client code
```c++
User *p = new User(this);
p->connectToHost("127.0.0.1", 8010);
p->sendMessage("Hello Neuron");
```
##### Server code
```c++
NeuronServer *serverManager = new NeuronServer(8010, this);
serverManager->registerType<User*>();
connect(serverManager, &NeuronServer::peerConnected, this, [this] (NeuronPeer *p) {
    User *user = qobject_cast<User*>(p);
    qDebug() << "New player connected to server";

    connect(user, &User::sendMessageSignal, this, [this] (QString message) {
        qDebug() << "New message from a player;" << message;
    });
});
```
Nothing more! All done.
