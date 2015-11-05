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

    QString m_declType;
    QString m_name;
    QString m_returnType;
    QString m_signature;
    QString m_wrapperMacro;
    QString m_seprator;

    Class *parentClass;
public:
    explicit Method(QObject *parent = 0);

    QString declType() const;
    QString name() const;
    QString returnType() const;
    QString signature() const;
    QString wrapperMacro() const;
    QString seprator() const;

signals:
    void declTypeChanged(QString declType);
    void nameChanged(QString name);
    void returnTypeChanged(QString returnType);
    void signatureChanged(QString signature);
    void wrapperMacroChanged(QString wrapperMacro);
    void sepratorChanged(QString seprator);

public slots:
    void setDeclType(QString declType);
    void setName(QString name);
    void setReturnType(QString returnType);
    void setSignature(QString signature);
    void setWrapperMacro(QString wrapperMacro);
    void setSeprator(QString seprator);

private:
    QString replaceParams(QString text);
    QString getParametereNames();
    QString getParametereTypes();

};

#endif // METHOD_H
