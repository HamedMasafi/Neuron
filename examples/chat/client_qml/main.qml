import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
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

            User.sendImage(imageToSend.pixmap).then(function(){
                console.log(sent)
            })
        }
    }
    FileDialog{
        id: avatorChanger
        nameFilters: ["Images (*.png *.xpm *.jpg)"]

        onAccepted: {
            userAvator.load(avatorChanger.fileUrl)
            User.avator = userAvator.pixmap
        }
    }
    Pixmap{
        id: imageToSend
        visible: false
    }
/*
    SimpleTokenValidator{
        id: tokenValidator
        validateToken: RPC_TOKEN
    }
    Hub{
        id: hub
        encoder: tokenValidator
        isAutoReconnect: true
    }
    User{
        id: user
        hub: hub

//        onMessageRecivedSignal: {
//            var s = '<b><font color=' +
//                    (username == user.username ? "red" : "blue") +
//                    '>' +
//                    username +
//                    ' :</font></b> ' +
//                    message;
//            messages.append(s)
//        }
    }
    ServerInstance{
        id: server
        hub: hub

//        onBroadcastMessageSignal: {
//            messageBox.text = message
//            messageBox.open()
//        }

//        onImageSentSignal: {
//            var s = '<b>' + username + ' sent an image, but image show is not supported in qml version</b> ';

//            messages.append(s)
//        }
    }

    Component.onCompleted: {
        User.hub = hub
        server.hub = hub
    }*/

    Connections{
        target: User
        onMessageRecivedSignal: {
            var s = '<b><font color=' +
                    (username === User.username ? "red" : "blue") +
                    '>' +
                    username +
                    ' :</font></b> ' +
                    message;
            messages.append(s)
        }
    }
    Connections{
        target: Server

        onBroadcastMessageSignal: {
            messageBox.text = message
            messageBox.open()
        }

        onImageSentSignal: {
            var s = '<b>' + username + ' sent an image, but image show is not supported in qml version</b> ';

            messages.append(s)
        }
    }

    Flipable {
        id: flipable
        anchors.fill: parent

        anchors.margins: 20
        property bool flipped: false

        front: Item {
            anchors.fill: parent
            Pane {
                anchors.centerIn: parent
                ColumnLayout{

                    anchors.centerIn: parent
                    //                margins: 20

//                    Rectangle{
//                        anchors.fill: parent
//                        anchors{
//                            leftMargin: -20
//                            topMargin: -20
//                            bottomMargin: -20
//                            rightMargin: -20
//                        }
//                    }

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
                            Hub.serverAddress = serverAddress.text
                            //                        hub.port = PORT
                            Hub.connectToHost(true)
                            User.username = username.text
                            flipable.flipped = true
                        }
                    }
                }
        }
        }
        back: Item {
            anchors.fill: parent

            ColumnLayout{
                anchors.fill: parent

                Label {
                    text: qsTr("Note: some features like send image or change avator does not work in qml!")
                }
                RowLayout{
                    Pixmap{
                        id: userAvator
                        height: 50
                        width: 50
                    }
                    ColumnLayout{
                        Label {
                            text: User.username
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
                    Frame {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        TextArea{
                            id: messages

                            textFormat: TextEdit.RichText
                            readOnly: true
                            anchors.fill: parent
                        }
                    }

                    Frame {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 200
                        ListView{
                            clip: true
                            model: Server.users
                            anchors.fill: parent
                            delegate: RowLayout{
                                Pixmap{
                                    pixmapVariant: Server.users[index].avator
                                    height: 35
                                    width: 35
                                }
                                Text {
                                    text: Server.users[index].username
                                }
                            }
                        }
                    }

                }
                RowLayout{
                    Layout.fillWidth: true

                    TextField{
                        id: userMessage
                        Layout.fillWidth: true
//                        Layout.fillHeight: true
                    }
                    ColumnLayout{
                        Button{
                            text: "Send"
                            Layout.alignment: Qt.AlignTop

                            onClicked: {
                                User.sendMessage(userMessage.text)/*.then(function(){

                                })*/
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
//                        Item{
//                            Layout.fillHeight: true
//                        }
                    }
                }
            }
        }

        transform: Rotation {
            id: rotation
            angle: 0
            origin{
                x: flipable.width/2
                y: flipable.height/2
            }
            axis{
                x: 0
                y: 1
                z: 0
            }
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

    footer: RowLayout{
        Label {
            text: Hub.isConnected ? "Connected" : "Disconnected"
        }
    }
}
