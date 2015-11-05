import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3

Item {
    width: 800
    height: 600

    ColumnLayout{
        anchors.fill: parent

        RowLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            TextArea{
                readOnly: true
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ListView{
                Layout.preferredWidth: 200
                Layout.minimumWidth: 100
                Layout.fillHeight: true
            }
        }
        RowLayout{
            Layout.fillWidth: true

            TextArea{
                Layout.fillWidth: true
                Layout.maximumHeight: 160
            }
            Button{
                text: "Send"
                Layout.alignment: Qt.AlignTop
            }
        }
    }
}
