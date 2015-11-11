#ifndef METHOD_H
#define METHOD_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Class;
class Method : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString declType READ declType WRITE setDeclType NOTIFY declTypeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString returnType READ returnType WRITE setReturnType NOTIFY returnTypeChanged)
    Q_PROPERTY(QString signature READ signature WRITE setSignature NOTIFY signatureChanged)
    Q_PROPERTY(QString wrapperMacro READ wrapperMacro WRITE setWrapperMacro NOTIFY wrapperMacroChanged)
    Q_PROPERTY(QString seprator READ seprator WRITE setSeprator NOTIFY sepratorChanged)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(bool isInvokable READ isInvokable WRITE setIsInvokable NOTIFY isInvokableChanged)

public:
    explicit Method(QObject *parent = 0);

    QString declare();
    QString implement();
    QString getParametereNames();
    QString getParametereTypes();

    QString declType() const;
    QString name() const;
    QString returnType() const;
    QString signature() const;
    QString wrapperMacro() const;
    QString seprator() const;
    QString code() const;
    bool isInvokable() const;

signals:
    void declTypeChanged(QString declType);
    void nameChanged(QString name);
    void returnTypeChanged(QString returnType);
    void signatureChanged(QString signature);
    void wrapperMacroChanged(QString wrapperMacro);
    void sepratorChanged(QString seprator);
    void codeChanged(QString code);
    void isInvokableChanged(bool isInvokable);

public slots:
    void setDeclType(QString declType);
    void setName(QString name);
    void setReturnType(QString returnType);
    void setSignature(QString signature);
    void setWrapperMacro(QString wrapperMacro);
    void setSeprator(QString seprator);
    void setCode(QString code);
    void setIsInvokable(bool isInvokable);

private:
    QString replaceParams(QString text);

    Class *parentClass;

    QString m_declType;
    QString m_name;
    QString m_returnType;
    QString m_signature;
    QString m_wrapperMacro;
    QString m_seprator;
    QString m_code;
    bool m_isInvokable;
};

#endif // METHOD_H
