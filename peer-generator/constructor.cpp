//#include "constructor.h"

//#include "defines.h"

//#include <QRegularExpression>

//Constructor::Constructor(QObject *parent) : Method(parent)
//{

//}

//void Constructor::addVariableSet(QString name, QString value)
//{
//    variables.insert(name, value);
//}

//QString Constructor::implement()
//{
//    if(declType() == "signals")
//        return QString::null;

//    QString ret = QString("%1 %5::%2(%3)%6" LB "{" LB "%4}")
//            .arg(returnType())
//            .arg(name())
//            .arg(signature().replace(QRegularExpression("\\s*=\\s*\\S*"), ""))
//            .arg(code())
//            .arg(parentClass->name())
//            .arg(inheristanceDeclare().isNull() ? "" : " : " +inheristanceDeclare());

//    if(!wrapperMacro().isNull()){
//        if(wrapperMacro().contains("<") || wrapperMacro().contains(">") || wrapperMacro().contains("=") )
//            ret.prepend("#if " + wrapperMacro() + LB);
//        else
//            ret.prepend("#ifdef " + wrapperMacro() + LB);
//        ret.append("\n#endif");
//    }
//    return ret;
//}
