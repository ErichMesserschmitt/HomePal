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
    readonly property int minSize: 400

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
                text: _appController.status
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
                onClicked: {
                    _appController.restartClient()
                }
            }
        }
        RowLayout {
            id: roomsRow
            Layout.fillHeight: false;
            Layout.preferredHeight: root.height * 0.1
            Layout.fillWidth: true;
            property bool selectorVisible: roomList.length < 3 && roomList.length > 0
            property var roomList: _roomController ? _roomController.rooms : []
            property int selected: _roomController ? _roomController.selectedRoom : 0;

            CustomButton {
                id: leftRoom
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                visible: !roomsRow.selectorVisible
                text: "<"
                onClicked: {
                    roomsRow.selected = roomsRow.selected > 0 ? roomsRow.selected - 1 : roomsRow.roomList.length - 1
                    _roomController.selectedRoom = _roomController.rooms[roomsRow.selected].index
                }
            }

            CustomButton {
                id: currentRoom
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                Layout.preferredWidth: height
                visible: !roomsRow.selectorVisible
                enabled: false;
                text: roomsRow.roomList[roomsRow.selected].name
            }

            CustomButton {
                id: rightRoom
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                text: ">"
                visible: !roomsRow.selectorVisible
                onClicked: {
                    roomsRow.selected = roomsRow.selected < roomsRow.roomList.length - 1 ? roomsRow.selected + 1 : 0
                    _roomController.selectedRoom = _roomController.rooms[roomsRow.selected].index
                }
            }

            Repeater {
                model: roomsRow.selectorVisible ? _roomController ? _roomController.rooms : 0 : 0
                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    readonly property bool roomSelected: _roomController.rooms.length > 0 && index === _roomController.selectedRoom ? true : false
                    color: roomSelected ? Style.white : Style.semiTransparent

                    borderColor: roomSelected ? Style.darkOrange : Style.semiTransparentGrey
                    text: _roomController.rooms[index].name
                    textColor: _roomController.selectedRoom === _roomController.rooms[index].index ? Style.black : Style.white
                    onClicked: {
                        _roomController.selectedRoom = _roomController.rooms[index].index
                    }
                }
            }
            CustomButton {
                id: addRoom
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                text: "+"
                color: Style.semiTransparent
                borderColor: Style.white
                textColor: Style.white
                fontSize: height * 0.4
                radius: Style.defaultRadius
                onClicked: {
                    console.log("_roomController.components", _roomController.components.length)
                    createRoomNamePopup.open()
                }
            }
        }
        Flickable {
            id: flickableZone
            Layout.fillHeight: true;
            Layout.fillWidth: true;

            readonly property int columnSpacing: 2
            readonly property int proposedWidth: root.currentWidth - (root.currentWidth * 0.02 * 2)
            readonly property int proposedHeight: Math.max(proposedWidth * 0.25 - (columnSpacing * 3), root.minSize)
            readonly property int columns: proposedWidth / root.minSize
            readonly property int itemsCount: (_roomController ? _roomController.roomComponentsCount : 0) + 1
            readonly property int proposedRows: itemsCount / columns
            readonly property int rows: proposedRows * columns < itemsCount ? proposedRows + 1 : proposedRows


            contentHeight: proposedHeight * rows + ((rows + 2) * columnSpacing)
            contentWidth: width

            flickableDirection: Flickable.VerticalFlick
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            interactive: true

            GridLayout {
                id: modulesGrid
                anchors.fill: parent
                rows: flickableZone.rows
                columns: flickableZone.columns
                columnSpacing: 2

                Repeater {
                    id: blockRepeater
                    model: _roomController ? _roomController.components : 0
                    InfoBlock {
                        Layout.fillHeight: true;
                        Layout.maximumHeight: flickableZone.proposedHeight
                        Layout.minimumHeight: root.minSize
                        Layout.minimumWidth: root.minSize
                        Layout.fillWidth: true;
                        Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        Layout.preferredWidth: height
                        visible: _roomController ? _roomController.selectedRoom === 0 ? true : _roomController.selectedRoom === _roomController.components[index].roomIndex : false
                        readonly property var locale: Qt.locale()

                        name: _roomController.components[index].name
                        status: _roomController.components[index].enabled ? "Увімкнено" : "Вимкнено"
                        isAuto: _roomController.components[index].isAuto ? "Автоматичний" : "Ручний"


                        enabledAt: _roomController.components[index].enStr
                        disabledAt: _roomController.components[index].disStr
                        additionalInfo: _roomController.components[index].info

                        onSwitchClicked: {
                            if(_roomController){
                                console.log(_roomController.components[index].index)
                                _roomController.editComponent(_roomController.components[index].index);
                                _roomController.editableComponent.switchEnabled()
                                _roomController.saveEditComponent();
                            }
                        }
                        onDelayClicked: {
                            if(_roomController){
                                console.log(_roomController.components[index].index)
                                _roomController.editComponent(_roomController.components[index].index);
                                _roomController.editableComponent.switchAuto()
                                _roomController.saveEditComponent();
                            }
                        }
                        onDeleteClicked: {
                            if(_roomController){
                                console.log(_roomController.components[index].index, _roomController.components[index].name)
                                _roomController.removeComponent(_roomController.components[index].index);
                            }
                        }
                        onEditClicked: {
                            console.log(_roomController.components[index].index)
                            _roomController.editComponent(_roomController.components[index].index);
                            editComponentPopup.headerText = _roomController.editableComponent.name
                            editComponentPopup.open();
                        }
                    }
                }
                CustomButton {
                    Layout.fillHeight: true;
                    Layout.maximumHeight: flickableZone.proposedHeight
                    Layout.minimumHeight: root.minSize
                    Layout.minimumWidth: root.minSize
                    Layout.fillWidth: true;
                    Layout.preferredWidth: height
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    text: "+"
                    color: Style.semiTransparent
                    borderColor: Style.white
                    textColor: Style.white
                    fontSize: height * 0.4
                    radius: Style.defaultRadius
                    onClicked: {
                        _roomController.requestNewDevices();
                        createComponentNamePopup.open();
                    }
                }
            }
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
                text: "Змінити"
                onClicked: {
                    editRoomNamePopup.open()
                }
            }
            CustomButton {
                Layout.fillHeight: true;
                Layout.fillWidth: false;
                Layout.preferredWidth: height
                borderColor: Qt.darker(Style.darkGrey, 1.5)
                color: Style.red
                image: Style.trashcan
                onClicked: {
                    console.log(_roomController.rooms[_roomController.selectedRoom].index, _roomController.rooms[_roomController.selectedRoom].name)
                    _roomController.removeRoom(_roomController.rooms[_roomController.selectedRoom].index)
                    _roomController.selectedRoom = 0;
                }
            }
        }
    }
    Popup {
        id: createRoomNamePopup
        width: root.width
        height: root.height
        modal: true
        dim: true
        focus: true
        background: Rectangle {
            color: Style.transparent
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: SelectName {
            headerText: "Створення назви кімнати"
            onAccepted: function(name) {
                console.log("createRoomNamePopup::accepted", name)
                _roomController.addRoom(name);
                createRoomNamePopup.close();
            }
            onDeclined:{
                createRoomNamePopup.close();
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
        contentItem: SelectName {
            headerText: "Зміна назви кімнати"
            onAccepted: function(name) {
                console.log("editRoomNamePopup::accepted", name)
                editRoomNamePopup.close();
                _roomController.editRoom(_roomController.selectedRoom);
                _roomController.editableRoom.name = name
                _roomController.saveEditRoom();
            }
            onDeclined:{
                editRoomNamePopup.close();
            }
        }
    }

    Popup {
        id: createComponentNamePopup
        width: root.width
        height: root.height
        modal: true
        dim: true
        focus: true
        background: Rectangle {
            color: Style.transparent
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: DevicesList {
            headerText: "Компонент для " + _roomController.rooms[_roomController.selectedRoom].name
            onAccepted: {
                createComponentNamePopup.close();
            }
            onDeclined:{
                createComponentNamePopup.close();
            }
        }
    }
    Popup {
        id: editComponentPopup
        width: root.width
        height: root.height
        modal: true;
        dim: true;
        focus: true;
        background: Rectangle {
            color: Style.semiTransparent

        }
        property string headerText: "Помилка вибору компонента"
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: EditParams {
            headerText: editComponentPopup.headerText
            onAccepted: {
                _roomController.saveEditComponent();
                editComponentPopup.close();
            }
            onDeclined:{
                editComponentPopup.close();
            }
        }
    }

}
