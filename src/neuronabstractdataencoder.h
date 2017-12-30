#ifndef NEURONABSTRACTDATAENCODER_H
#define NEURONABSTRACTDATAENCODER_H

#include <QVariantMap>

class NeuronAbstractDataEncoder
{
public:
    NeuronAbstractDataEncoder();

    virtual void encrypt(QVariantMap &map) = 0;
    virtual bool decrypt(QVariantMap &map) = 0;
};

#endif // NEURONABSTRACTDATAENCODER_H
