#include "texthelper.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QStringList>

TextHelper::TextHelper(QObject *parent) : QObject(parent)
{
    QDir rDir(":/snippets");
    QStringList resfiles = rDir.entryList();
    foreach (QString file, resfiles) {
        QFile fres(":/snippets/" + file);
        fres.open(QIODevice::ReadOnly);
        files.insert(file, fres.readAll());
        fres.close();
    }
}

TextHelper::~TextHelper()
{

}

TextHelper *TextHelper::instance()
{
    static TextHelper *instance = 0;

    if(!instance)
        instance = new TextHelper;

    return instance;
}

QString TextHelper::getFileContent(QString fileName)
{
    if(!files.contains(fileName))
        qDebug() << fileName << "does not exists";

    return files[fileName];
}

QString TextHelper::indent(QString text)
{
    return "    " + text.replace("\n", "\n    ");
}

bool TextHelper::hasOperatorEqual(QString type)
{
    if(type.startsWith("Q"))
        type.remove(0, 1);
    type = type.toLower();
    QString types =
            "_int_"
            "_long_"
            "_double_"
            "_bool_"
            "_float_"
            "_bitarray_"
            "_bitmap_"
            "_bool_"
            "_brush_"
            "_bytearray_"
            "_char_"
            "_color_"
            "_cursor_"
            "_date_"
            "_datetime_"
            "_double_"
            "_easingcurve_"
            "_uuid_"
            "_modelindex_"
            "_persistentmodelindex_"
            "_font_"
            "_hash_"
            "_icon_"
            "_image_"
            "_int_"
            "_keysequence_"
            "_line_"
            "_linef_"
            "_list_"
            "_locale_"
            "_longlong_"
            "_map_"
            "_matrix_"
            "_transform_"
            "_matrix4x4_"
            "_palette_"
            "_point_"
            "_pointf_"
            "_polygon_"
            "_polygonf_"
            "_quaternion_"
            "_rect_"
            "_rectf_"
            "_regexp_"
            "_regularexpression_"
            "_region_"
            "_size_"
            "_sizef_"
            "_sizepolicy_"
            "_string_"
            "_stringlist_"
            "_textformat_"
            "_textlength_"
            "_time_"
            "_uint_"
            "_ulonglong_"
            "_url_"
            "_vector2d_"
            "_vector3d_"
            "_vector4d_";

    return types.contains("_" + type + "_");
}

