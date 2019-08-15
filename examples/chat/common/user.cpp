#include "user.h"


#include <QMetaObject>
#include <QMetaMethod>

N_CLASS_IMPL(User)
{

}

N_PROPERTY_IMPL(User, QString, username, username, setUsername, usernameChanged)
N_PROPERTY_IMPL(User, QPixmap, avator, avator, setAvator, avatorChanged)

N_REMOTE_METHOD_IMPL(User, messageRecived, QString, username, QString, message)
N_REMOTE_METHOD_IMPL(User, sendImage, QPixmap, image)
N_REMOTE_METHOD_IMPL(User, sendMessage, QString, message)
