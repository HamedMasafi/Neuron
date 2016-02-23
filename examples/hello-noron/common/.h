#ifndef CLIENT
#define CLIENT

class Client : public NoronHub
{




public slots:
    #ifdef QT_QML_LIB
    int getRandomNumber(QJSValue callbackFunction);
    #endif
    #if __cplusplus >= 201103L
    int getRandomNumber(std::function<void(int)> callbackFunction);
    #endif
    int getRandomNumber(const QObject *obj, char *callbackSlot);
    int getRandomNumber();
    int getRandomNumber(const QObject *obj, const QMetaMethod *callbackMethod);
    int getRandomNumberAsync();
    int getRandomNumberSlot();

signals:
    int getRandomNumberSignal(, int returnValue);

};
#endif // CLIENT
