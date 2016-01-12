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

    FileDialog{
        id: imageSelector
        nameFilters: ["Images (*.png *.xpm *.jpg)"]

        onAccepted: {
            imageToSend.load(imageSelector.fileUrl)

            user.sendImage(imageToSend.pixmap, function(){
                console.log(sent)
            })
        }
    }
    FileDialog{
        id: avatorChanger
        nameFilters: ["Images (*.png *.xpm *.jpg)"]

        onAccepted: {
            userAvator.load(avatorChanger.fileUrl)
            user.avator = userAvator.pixmap
        }
    }
    Pixmap{
        id: imageToSend
        visible: false
    }

    Hub{
        id: hub
        validateToken: RPC_TOKEN
        autoReconnect: true
    }
    User{
        id: user
        hub: hub

        onMessageRecivedSignal: {
            var s = '<b><font color=' +
                    (username == user.username ? "red" : "blue") +
                    '>' +
                    username +
                    ' :</font></b> ' +
                    message;
            messages.append(s)
        }
    }
    Server{
        id: server
        hub: hub

        onBroadcastMessageSignal: {
            messageBox.text = message
            messageBox.open()
        }

        onImageSentSignal: {
            var s = '<b>' + username + ' sent an image, but image show is not supported in qml version</b> ';

            messages.append(s)
        }
    }

    Component.onCompleted: {
        hub.addSharedObject(user)
        hub.addSharedObject(server)
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
                    text: "Username"
                }
                TextField{
                    id: username
                }

                Button{
                    text: "Login"
                    onClicked: {
                        hub.connectToServer(serverAddress.text, PORT)
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

                Text {
                    text: qsTr("Note: some features like send image or change avator does not work in qml!")
                }
                RowLayout{
                    Pixmap{
                        id: userAvator
                        height: 50
                        width: 50
                    }
                    ColumnLayout{
                        Text {
                            text: user.username
                        }
                        Button{
                            text: "Change avator"
                            onClicked: avatorChanger.open()
                        }
                    }
                }

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
                        ListView{
                            clip: true
                            model: server.users
                            anchors.fill: parent
                            delegate: RowLayout{
                                Pixmap{
                                    pixmapVariant: server.users[index].avator
                                    height: 35
                                    width: 35
                                }
                                Text {
                                    text: server.users[index].username
                                }
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
                    ColumnLayout{
                        Layout.maximumHeight: 160
                        Button{
                            text: "Send"
                            Layout.alignment: Qt.AlignTop

                            onClicked: {
                                user.sendMessage(userMessage.text)
                                userMessage.text = ''
                            }
                        }
                        Button{
                            text: "Send image"
                            Layout.alignment: Qt.AlignTop

                            onClicked: {
                                imageSelector.open()
                            }
                        }
                        Item{
                            Layout.fillHeight: true
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
            NumberAnimation { target: rotation; property: "angle"; duration: 400 }
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
