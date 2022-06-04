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
        color: Style.semiTransparentPress
    }
    property string headerText: "Create name"
    signal accepted(string name)
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
            anchors.margins: root.height * 0.05
            Rectangle {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height * 0.15
                Layout.fillWidth: true;
                radius: Style.defaultRadius
                color: Style.darkOrange
                Text {
                    anchors.fill: parent;
                    text: root.headerText
                    font.family: Style.fontMain.name
                    color: Style.white
                    leftPadding: Style.defaultRadius * 2
                    rightPadding: leftPadding
                    font.pixelSize: height * 0.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Item {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
            }

            Rectangle {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height * 0.15
                Layout.fillWidth: true;
                color: Style.white
                radius: Style.defaultRadius
                border.width: Style.defaultWidth
                border.color: textInput.activeFocus ? Style.blue : Style.orange

                TextInput {
                    id: textInput
                    anchors.fill: parent;
                    font.family: Style.fontMain.name
                    leftPadding: Style.defaultRadius * 2
                    rightPadding: leftPadding
                    font.pixelSize: height * 0.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    maximumLength: 30
                    clip: true;
                }
                Text {
                    anchors.fill: parent;
                    visible: textInput.text.length === 0 && !textInput.activeFocus
                    text: "Enter text"
                    color: Style.lightGrey
                    font.family: Style.fontMain.name
                    leftPadding: Style.defaultRadius * 2
                    rightPadding: leftPadding
                    font.pixelSize: height * 0.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Item {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
            }

            RowLayout {
                Layout.fillHeight: false;
                Layout.preferredHeight:  mainBlock.height * 0.15
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
                        root.accepted(textInput.text)
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
