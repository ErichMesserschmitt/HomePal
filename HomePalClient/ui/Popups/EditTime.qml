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

    property int initHE: 0
    property int initME: 0
    property int initHD: 0
    property int initMD: 0

    signal accepted(int hE, int mE, int hD, int mD)
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
                Layout.fillHeight: true;
                Layout.preferredHeight: root.height * 0.15
                Layout.fillWidth: false;
                Layout.preferredWidth: height * 1.6
                Layout.alignment: Qt.AlignHCenter
                color: Style.white
                radius: Style.defaultRadius
                border.width: Style.defaultWidth
                border.color: textInput.activeFocus ? Style.blue : Style.orange

                GridLayout {
                    anchors.fill: parent;
                    anchors.margins: Style.defaultRadius
                    rows: 2
                    columns: 4
                    Text {
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        Layout.row: 0
                        Layout.column: 0
                        font.family: Style.fontMain.name
                        font.pixelSize: height * 0.35
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "ON"
                        color: Style.green
                    }
                    Text {
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        Layout.row: 1
                        Layout.column: 0
                        font.family: Style.fontMain.name
                        font.pixelSize: height * 0.35
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "OFF"
                        color: Style.red
                    }

                    ComboBox {
                        id: hourE
                        Layout.fillHeight: true;
                        Layout.fillWidth: false;
                        Layout.preferredWidth: height
                        Layout.row: 0
                        Layout.column: 1
                        currentIndex: initHE
                        model: 24
                        width: 200
                        font.family: Style.fontMain.name
                        font.pixelSize: height * 0.55
                        background: Rectangle {
                            color: Style.white
                            border.color: Style.green
                            radius: Style.defaultRadius
                            border.width: 3
                        }

                    }
                    Text {
                        Layout.fillHeight: true;
                        Layout.fillWidth: false;
                        Layout.preferredWidth: height / 3
                        Layout.row: 0
                        Layout.column: 2
                        font.family: Style.fontMain.name
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: ":"
                        font.pixelSize: height
                        color: Style.black
                    }

                    ComboBox {
                        id: minE
                        Layout.fillHeight: true;
                        Layout.fillWidth: false;
                        Layout.preferredWidth: height
                        Layout.row: 0
                        Layout.column: 3
                        currentIndex: initME
                        model: 60
                        width: 200
                        font.family: Style.fontMain.name
                        font.pixelSize: height * 0.55
                        background: Rectangle {
                            color: Style.white
                            border.color: Style.green
                            radius: Style.defaultRadius
                            border.width: 3
                        }
                    }
                    ComboBox {
                        id: hourD
                        Layout.fillHeight: true;
                        Layout.fillWidth: false;
                        Layout.preferredWidth: height
                        Layout.row: 1
                        Layout.column: 1
                        currentIndex: initHD
                        model: 24
                        width: 200
                        font.family: Style.fontMain.name
                        font.pixelSize: height * 0.55
                        background: Rectangle {
                            color: Style.white
                            border.color: Style.red
                            radius: Style.defaultRadius
                            border.width: 3
                        }
                    }
                    Text {
                        Layout.fillHeight: true;
                        Layout.fillWidth: false;
                        Layout.preferredWidth: height / 3
                        Layout.row: 1
                        Layout.column: 2
                        font.family: Style.fontMain.name
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: ":"
                        font.pixelSize: height
                        color: Style.black
                    }
                    ComboBox {
                        id: minD
                        Layout.fillHeight: true;
                        Layout.fillWidth: false;
                        Layout.preferredWidth: height
                        Layout.row: 1
                        Layout.column: 3
                        currentIndex: initMD
                        model: 60
                        width: 200
                        font.family: Style.fontMain.name
                        font.pixelSize: height * 0.55
                        background: Rectangle {
                            color: Style.white
                            border.color: Style.red
                            radius: Style.defaultRadius
                            border.width: 3
                        }
                    }
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
                        root.accepted(hourE.currentIndex, minE.currentIndex, hourD.currentIndex, minD.currentIndex);
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
