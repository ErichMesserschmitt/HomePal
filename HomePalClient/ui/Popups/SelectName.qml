import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.2
import QtQuick.Dialogs

import "../Components"
import "../Items"

Item {
    id: root;

    Rectangle {
        id: background;
        anchors.fill: parent;
        color: Style.semiTransparent
    }

    signal accepted(var name)
    signal declined()
    Rectangle {
        id: mainBlock
        anchors.centerIn: parent;
        height: root.height * 0.7
        width: root.width * 0.7
        radius: Style.defaultRadius
        color: Style.white
        ColumnLayout {
            anchors.fill: mainBlock
            anchors.margins: root.height * 0.1
            Rectangle {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height * 0.3
                Layout.fillWidth: true;
                radius: Style.defaultRadius
                color: Style.darkOrange
                Text {
                    anchors.fill: parent;
                    text: "Enter name"
                    font.family: Style.fontMain.name
                    color: Style.white
                }
            }
            Item {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                TextInput {
                    id: textInput
                    anchors.centerIn: parent;
                    height: mainBlock.height * 0.3
                    width: parent.width
                }
            }


            RowLayout {
                Layout.fillHeight: false;
                Layout.preferredHeight:  mainBlock.height * 0.3
                Layout.fillWidth: true;

                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color: Style.white
                    borderColor: Style.homeScreenGreen
                    radius: Style.defaultRadius
                    text: "OK"
                    textColor: Style.homeScreenGreen
                    onClicked: {
                        root.accepted("textInput.text")
                    }
                }
                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color: Style.white
                    borderColor: Style.red
                    textColor: Style.red
                    radius: Style.defaultRadius
                    text: "Cancel"
                    onClicked: {
                        root.declined()
                    }
                }
            }
        }
    }
}
