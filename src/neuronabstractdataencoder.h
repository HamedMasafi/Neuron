#ifndef NEURONABSTRACTDATAENCODER_H
#define NEURONABSTRACTDATAENCODER_H

#include <QObject>
#include <QVariantMap>

class NeuronAbstractDataEncoder : public QObject
{
    Q_OBJECT
public:
    NeuronAbstractDataEncoder(QObject *parent = Q_NULLPTR);

    virtual void encrypt(QVariantMap &map) = 0;
    virtual bool decrypt(QVariantMap &map) = 0;
};

#endif // NEURONABSTRACTDATAENCODER_H
