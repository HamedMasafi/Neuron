import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import Tooj.RPC 1.0

ApplicationWindow {
    title: qsTr("RPC Chat Client (qml version)")
    width: 640
    height: 480
    visible: true

    MessageDialog{
        id: messageBox
        icon: StandardIcon.Warning
    }

    Hub{
        id: hub
        validateToken: RPC_TOKEN
        autoReconnect: true
    }
    User{
        id: user
        hub: hub

        onMessageRecivedHandle: {
            var s = '<b><font color=' +
                        (username == user.username ? "red" : "blue") +
                        '>' +
                        username +
                        ' :</font></b> ' +
                        message;
            messages.append(s)
            console.log(s)
        }
        onRoomMessageHandle: {

        }
    }
    Server{
        id: server
        hub: hub

        onBroadcastMessageHandle: {
            messageBox.text = message
            messageBox.open()
        }


        onUsersChanged: {
            //            var users = []
            usersModel.clear()

            var i
            for(i = 0; i < server.users.length; i++)
                usersModel.append({text: server.users[i]})
            //            console.log(server.users)
        }

    }

    Component.onCompleted: {
        //        hub.connectToServer("127.0.0.1", 8099)
        hub.addSharedObject(user)
        hub.addSharedObject(server)
    }

    ListModel{
        id: usersModel

    }
    Flipable {
        id: flipable
        anchors.fill: parent

        anchors.margins: 20
        property bool flipped: false

        front: Item {
            anchors.fill: parent
            ColumnLayout{
                anchors.centerIn: parent
                //                margins: 20

                Rectangle{
                    anchors.fill: parent
                    anchors{
                        leftMargin: -20
                        topMargin: -20
                        bottomMargin: -20
                        rightMargin: -20
                    }
                }

                Text {
                    text: "Server address"
                }
                TextField{
                    id: serverAddress
                    text: "127.0.0.1"
                }

                Text {
                    text: "Port"
                }
                TextField{
                    id: port
                    text: '8099'
                }

                Text {
                    text: "Username"
                }
                TextField{
                    id: username
                }

                Button{
                    text: "Login"
                    onClicked: {
                        hub.connectToServer(serverAddress.text, port.text)
                        user.username = username.text
                        flipable.flipped = true
                    }
                }
            }
        }
        back: Item {
            anchors.fill: parent

            ColumnLayout{
                anchors.fill: parent

                RowLayout{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    TextArea{
                        id: messages

                        textFormat: TextEdit.RichText
                        readOnly: true
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                    Rectangle{
                        Layout.fillHeight: true
                        Layout.preferredWidth: 200
                        clip: true

                        Text {
                            text: "Users count: " + usersModel.count
                        }
                        ListView{
                            clip: true
                            model: usersModel
                            anchors.fill: parent
                            anchors.topMargin: 40
                            //                        Layout.minimumWidth: 100
                            //                        Layout.fillWidth: true
                            //width: 200
                            delegate: Text {
                                text: index + "# " + model.text
                            }
                        }
                    }
                }
                RowLayout{
                    Layout.fillWidth: true

                    TextArea{
                        id: userMessage
                        Layout.fillWidth: true
                        Layout.maximumHeight: 160
                    }
                    Button{
                        text: "Send"
                        Layout.alignment: Qt.AlignTop

                        onClicked: {
                            user.sendMessage(userMessage.text)
                            userMessage.text = ''
                        }
                    }
                }
            }
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
            angle: 0    // the default angle
        }

        states: State {
            name: "back"
            PropertyChanges { target: rotation; angle: 180 }
            when: flipable.flipped
        }

        transitions: Transition {
            NumberAnimation { target: rotation; property: "angle"; duration: 800 }
        }
    }

    statusBar: StatusBar{
        RowLayout {
            anchors.fill: parent
            Label {
                text: hub.isConnected ? "Connected" : "Disconnected"
            }
        }
    }
}
