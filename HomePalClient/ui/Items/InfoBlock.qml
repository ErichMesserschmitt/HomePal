import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Layouts 1.2
import QtQuick.Dialogs
import QtQuick.Controls 2.12
import "../Components"

Rectangle {
    id: root
    radius: Style.defaultRadius
    border.width: 2
    border.color: Style.transparent
    property string name: "Undefined"
    property string status: "Disabled"
    property string enabledAt: "00:00 AM"
    property string disabledAt: "00:00 AM"
    property string additionalInfo: "Currently no info\nsoon will be updated"

    RowLayout {
        anchors.fill: parent;
        anchors.margins: Style.defaultWidth
        spacing: 2
        ColumnLayout {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            spacing: 2
            Rectangle {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height / 6
                Layout.fillWidth: true;
                radius: Style.defaultRadius
                color: Style.darkOrange
                Text {
                    anchors.fill: parent;
                    text: root.name
                    font.pointSize: parent.height * 0.6
                    color: Style.white
                    font.family: Style.fontMain.name
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter

                }
            }
            Rectangle {
                Layout.fillHeight: false;
                Layout.fillWidth: true;
                Layout.preferredHeight: (parent.height * 0.1) * 3
                radius: Style.defaultRadius
                color: Style.orange
                Text {
                    anchors.fill: parent;
                    anchors.margins: parent.height * 0.1
                    text: "Status: " + root.status + "<br>"
                    + "Enable At: " + root.enabledAt + "<br>"
                    + "Disable At: " + root.disabledAt
                    font.pointSize: parent.height * 0.1
                    color: Style.white
                    font.family: Style.fontMain.name
                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter

                }
            }
            Rectangle {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                radius: Style.defaultRadius
                color: Style.lightGrey
                Text {
                    anchors.fill: parent;
                    anchors.margins: parent.height * 0.1
                    text: root.additionalInfo
                    font.pointSize: parent.height * 0.1
                    color: Style.black
                    font.family: Style.fontMain.name
                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter
                    wrapMode: Text.WordWrap
                }
            }
        }
        ColumnLayout {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            //Layout.minimumWidth: root.height * 0.25
            spacing: 1
            CustomButton {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height / 6
                Layout.fillWidth: false;
                Layout.preferredWidth: root.height / 6
                color: Style.red
                borderWidth: 0
                image: Style.trashcan
                onClicked: {
                    console.log("H", root.height, "W", root.width)
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: parent.radius
                    color: parent.color
                    z: parent.z - 1
                }

            }
            CustomButton {
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: root.height / 6
                color: Style.orange
                radius: 0
                borderWidth: 0
                isHorizontal: false;
                text: "Edit"
                fontFamily: Style.fontMain.name
                textColor: Style.white
            }
            CustomButton {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height / 6
                Layout.fillWidth: false;
                Layout.preferredWidth: root.height / 6
                borderWidth: 0
                color: Style.blue
                radius: 0
                image: Style.delay
            }
            CustomButton {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height / 6
                Layout.fillWidth: false;
                Layout.preferredWidth: root.height / 6
                borderWidth: 0
                color: Style.red
                image: Style.onoff
                Rectangle {
                    anchors.top: parent.top
                    width: parent.width
                    height: parent.radius
                    color: parent.color
                    z: parent.z - 1
                }
            }
        }
    }
}

