#ifndef CLIENT
#define CLIENT

class Client : public NoronHub
{




public slots:
    int getRandomNumber(const QObject *obj, const QMetaMethod *callbackMethod);
    #if __cplusplus >= 201103L
    int getRandomNumber(std::function<void(int)> callbackFunction);
    #endif
    int getRandomNumber(const QObject *obj, char *callbackSlot);
    int getRandomNumber();
    #ifdef QT_QML_LIB
    int getRandomNumber(QJSValue callbackFunction);
    #endif
    int getRandomNumberAsync();
    int getRandomNumberSlot();
    int getRandomNumberWithTimeout(int timeout, const QObject *obj, char *callbackSlot);
    int getRandomNumberWithTimeout(int timeout);
    int getRandomNumberWithTimeout(int timeout, const QObject *obj, const QMetaMethod *callbackMethod);
    #if __cplusplus >= 201103L
    int getRandomNumberWithTimeout(int timeout, std::function<void(int)> callbackFunction);
    #endif
    #ifdef QT_QML_LIB
    int getRandomNumberWithTimeout(int timeout, QJSValue callbackFunction);
    #endif
    int getRandomNumberWithTimeoutAsync(int timeout);
    int getRandomNumberWithTimeoutSlot(int timeout);

signals:
    int getRandomNumberSignal(, int returnValue);
    int getRandomNumberWithTimeoutSignal(int timeout, , int returnValue);

};
#endif // CLIENT
