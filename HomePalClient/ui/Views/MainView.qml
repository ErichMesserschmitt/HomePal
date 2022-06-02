import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.2
import QtQuick.Dialogs
import "../Components"
import "../Items"
import "../Popups"

Item {
    id: root
    Background {
        anchors.fill: parent;
    }
    property int currentWidth: 0;
    readonly property int minSize: 400 //pixels

    Item {
        id: backgroundShade
        anchors.fill: parent;
        anchors.margins: root.width * 0.015
        Rectangle {
            anchors.fill: parent;
            color: Style.semiTransparentPress
            radius: Style.defaultRadius
        }
    }

    ColumnLayout {
        id: parentLayout
        anchors.fill: parent;
        anchors.margins: root.currentWidth * 0.02
        RowLayout {
            id: statusAndConnection
            Layout.fillHeight: false;
            Layout.preferredHeight: root.height * 0.1
            Layout.fillWidth: true;
            CustomButton {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                color: Qt.darker(Style.darkOrange, 1.8)
                borderColor: Qt.darker(Style.darkOrange, 1.5)
                textColor: Style.white
                fontSize: height * 0.5
                fontFamily: Style.fontMain.name
                text: "Connection Status"
            }
            CustomButton {
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                color: Qt.darker(Style.darkOrange, 1.8)
                borderColor: Qt.darker(Style.darkOrange, 1.5)
                textColor: Style.white
                fontSize: height * 0.5
                fontFamily: Style.fontMain.name
                image: Style.bluetooth
            }
        }
        RowLayout {
            Layout.fillHeight: false;
            Layout.preferredHeight: root.height * 0.1
            Layout.fillWidth: true;
            Repeater {
                model:  _roomController ? _roomController.rooms : 0
                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    readonly property bool roomSelected: _roomController.rooms.length > 0 && index === _roomController.selectedRoom ? true : false
                    color: roomSelected ? Style.white : Style.semiTransparent

                    borderColor: roomSelected ? Style.darkOrange : Style.semiTransparentGrey
                    text: _roomController.rooms[index].name
                    onClicked: {
                        _roomController.selectedRoom = index
                    }
                }
            }
            CustomButton {
                id: addRoom
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                text: "+"
                onClicked: {
                    _roomController.addRoom("Test room");
                    editRoomNamePopup.open()
                }
            }
        }

        GridLayout {
            id: modulesGrid
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            readonly property int contentWidth: root.currentWidth - (root.currentWidth * 0.02 * 2)
            rows: blockRepeater.model / columns
            columns: contentWidth / root.minSize
            columnSpacing: 2

            Repeater {
                id: blockRepeater
                model: 0//_roomController ? _roomController.rooms : 0
                InfoBlock {
                    Layout.fillHeight: true;
                    Layout.maximumHeight: Math.max(modulesGrid.contentWidth * 0.25 - (modulesGrid.columnSpacing * 3), root.minSize)
                    Layout.minimumHeight: root.minSize
                    Layout.minimumWidth: root.minSize
                    Layout.fillWidth: true;
                    Layout.preferredWidth: height
                    name: ""//_roomController.rooms[index].name
                }
            }
            CustomButton {
                Layout.fillHeight: true;
                Layout.maximumHeight: Math.max(modulesGrid.contentWidth * 0.25 - (modulesGrid.columnSpacing * 3), root.minSize)
                Layout.minimumHeight: root.minSize
                Layout.minimumWidth: root.minSize
                Layout.fillWidth: true;
                Layout.preferredWidth: height
                text: "+"
                color: Style.semiTransparent
                borderColor: Style.semiTransparentGrey
                textColor: Style.white
                radius: Style.defaultRadius
                onClicked: {
                    console.log("adding component")
                }
            }
        }

        Item {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
        }

        RowLayout {
            Layout.fillHeight: false;
            Layout.preferredHeight: root.height * 0.1
            Layout.fillWidth: true;
            CustomButton {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                color: Qt.darker(Style.darkGrey, 1.8)
                borderColor: Qt.darker(Style.darkGrey, 1.5)
                textColor: Style.white
                fontSize: height * 0.5
                fontFamily: Style.fontMain.name
                text: "Edit"
            }
            CustomButton {
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                borderColor: Qt.darker(Style.darkGrey, 1.5)
                color: Style.red
                image: Style.trashcan
            }
        }
    }
    Popup {
        id: editRoomNamePopup
        width: root.width
        height: root.height
        modal: true
        dim: true
        focus: true
        background: Rectangle {
            color: Style.transparent
        }

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        onOpened: {

        }

        contentItem: SelectName {
            id: updateInfoPopup
            onAccepted: {
                console.log("CLOSED", name)
                editRoomNamePopup.close();
            }
            onDeclined:{
                console.log("CLOSED")
                editRoomNamePopup.close();
            }

        }
    }

}
