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
    property string headerText: "Невідоме ім'я"

    signal accepted()
    signal declined()
    Rectangle {
        id: mainBlock
        anchors.centerIn: parent;
        height: root.height * 0.9
        width: root.width * 0.9
        radius: Style.defaultRadius
        color: Style.white
        ColumnLayout {
            anchors.fill: mainBlock
            anchors.margins: root.height * 0.01
            Rectangle {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height * 0.1
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
            Rectangle {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                Layout.alignment: Qt.AlignCenter
                color: Style.white
                radius: Style.defaultRadius
                border.width: Style.defaultWidth
                border.color: Style.orange
                ColumnLayout {
                    id: contentLayout
                    anchors.fill: parent;
                    anchors.margins: root.width * 0.03


                    Text {
                        Layout.fillHeight: false
                        Layout.preferredHeight: root.height * 0.03
                        Layout.fillWidth: true;
                        color: Style.black
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        text: "Автоматичний план:"
                        font.family: Style.fontMain.name
                        font.pixelSize: root.height * 0.03
                    }
                    Rectangle {
                        id: timeBlock
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        Layout.margins: root.height * 0.02
                        color: Style.lightGrey
                        radius: Style.defaultRadius
                        Flickable {
                            anchors.fill: parent;
                            readonly property int columnSpacing: 2

                            readonly property int proposedHeight: timeBlock.height * 0.3
                            readonly property int columns: _roomController && _roomController.editableComponent ? _roomController.editableComponent.enableAt.length + 1 : 1


                            contentHeight: columns * proposedHeight + (columns - 1) * columnSpacing
                            contentWidth: width

                            flickableDirection: Flickable.VerticalFlick
                            clip: true
                            boundsBehavior: Flickable.StopAtBounds

                            interactive: true

                            ColumnLayout {
                                anchors.fill: parent;
                                anchors.margins: 5
                                Layout.alignment: Qt.AlignTop
                                spacing: 2
                                Repeater{
                                    model:  _roomController && _roomController.editableComponent ? _roomController.editableComponent.enableAt.length : 0
                                    Rectangle {
                                        Layout.fillHeight: false;
                                        Layout.preferredHeight: timeBlock.height * 0.3
                                        Layout.fillWidth: true;
                                        color: Style.semiTransparent;
                                        radius: Style.defaultRadius
                                        ColumnLayout {
                                            anchors.fill: parent;
                                            Text {
                                                Layout.fillHeight: true;
                                                Layout.fillWidth: true;
                                                text: "ON  " + _roomController.editableComponent.enableAt[index]
                                                font.pixelSize: parent.height * 0.3
                                                leftPadding: 5
                                                color: Style.black
                                                font.family: Style.fontMain.name
                                                horizontalAlignment: Qt.AlignLeft
                                                verticalAlignment: Qt.AlignVCenter
                                                wrapMode: Text.WordWrap
                                            }
                                            Text {
                                                Layout.fillHeight: true;
                                                Layout.fillWidth: true;
                                                text: "OFF " + _roomController.editableComponent.disableAt[index]
                                                font.pixelSize: parent.height * 0.3
                                                leftPadding: 5
                                                color: Style.black
                                                font.family: Style.fontMain.name
                                                horizontalAlignment: Qt.AlignLeft
                                                verticalAlignment: Qt.AlignVCenter
                                                wrapMode: Text.WordWrap
                                            }
                                        }
                                        CustomButton {
                                            anchors.right: removeTimeButton.left
                                            height: parent.height
                                            width: height
                                            radius: Style.defaultRadius
                                            borderColor: Style.semiTransparent
                                            color: Style.orange
                                            text: "Edit"
                                            textColor: Style.white
                                            onClicked: {
                                                if(_roomController && _roomController.editableComponent) {
                                                    editTimePopup.index = index
                                                    editTimePopup.open();
                                                }
                                            }
                                        }
                                        CustomButton {
                                            id: removeTimeButton
                                            anchors.right: parent.right
                                            height: parent.height
                                            width: height
                                            borderColor: Style.semiTransparent
                                            radius: Style.defaultRadius
                                            color: Style.red
                                            image: Style.trashcan
                                            textColor: Style.white
                                            onClicked: {
                                                if(_roomController && _roomController.editableComponent)
                                                    _roomController.editableComponent.deleteTimePlan(index)
                                            }
                                        }
                                    }
                                }
                                CustomButton {
                                    Layout.fillHeight: false;
                                    Layout.preferredHeight: timeBlock.height * 0.3
                                    Layout.fillWidth: true;
                                    borderColor: Style.green
                                    radius: Style.defaultRadius
                                    color: Style.semiTransparent
                                    text: "Додати"
                                    textColor: Style.green
                                    onClicked: {
                                        addTimePopup.open()
                                    }
                                }
                                Item {
                                    Layout.fillHeight: true;
                                    Layout.fillWidth: true;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillHeight: false;
                        Layout.preferredHeight: root.height * 0.03
                        Layout.fillWidth: true;
                        color: Style.black
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        text: "Додаткові параметри:"
                        font.family: Style.fontMain.name
                        font.pixelSize: root.height * 0.03
                    }
                    Text {
                        Layout.fillHeight: false;
                        Layout.preferredHeight: root.height * 0.03
                        Layout.fillWidth: true;
                        color: Style.black
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        text: _roomController.editableComponent.value
                        font.family: Style.fontMain.name
                    }
                    Slider {
                        id: control
                        Layout.fillHeight: false;
                        Layout.preferredHeight:  root.height * 0.01
                        Layout.fillWidth: true;
                        from: _roomController && _roomController.editableComponent ? _roomController.editableComponent.lowPoint : 0
                        to: _roomController && _roomController.editableComponent ? _roomController.editableComponent.highPoint : 5
                        stepSize: _roomController && _roomController.editableComponent ? _roomController.editableComponent.delta : 0.1
                        snapMode: Slider.SnapOnRelease
                        value: _roomController && _roomController.editableComponent ? _roomController.editableComponent.value : 0
                        onValueChanged: {
                            console.log("value", value)
                            if(_roomController && _roomController.editableComponent){
                                _roomController.editableComponent.value = value;
                            }
                        }

                        handle: Rectangle {
                            x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
                            y: control.topPadding + control.availableHeight / 2 - height / 2
                            implicitWidth: root.height * 0.035
                            implicitHeight: root.height * 0.035
                            radius: root.height * 0.035 / 2
                            color: control.pressed ? Style.darkOrange : Style.orange
                            border.color: Style.transparent
                        }
                    }
                }


            }
            RowLayout {
                Layout.fillHeight: false;
                Layout.preferredHeight:  mainBlock.height * 0.1
                Layout.fillWidth: true;

                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color: Style.white
                    borderColor: Style.homeScreenGreen
                    radius: Style.defaultRadius
                    text: "Зберегти"
                    textColor: Style.homeScreenGreen
                    onClicked: {
                        root.accepted()
                    }
                }
                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color: Style.white
                    borderColor: Style.red
                    textColor: Style.red
                    radius: Style.defaultRadius
                    text: "Скасувати"
                    onClicked: {
                        root.declined()
                    }
                }
            }
        }
    }
    Popup {
        id: addTimePopup
        width: root.width
        height: root.height
        modal: true
        dim: true
        focus: true
        background: Rectangle {
            color: Style.transparent
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: EditTime {
            headerText: "Зміна часу"
            onAccepted: function(hE, mE, hD, mD) {
                console.log("addTimePopup::accepted", hE, mE, hD, mD)
                if(_roomController && _roomController.editableComponent){
                    console.log("addTimePopup::accepted", hE, mE, hD, mD)
                    _roomController.editableComponent.addTimePlan(hE, mE, hD, mD)
                }

                addTimePopup.close();
            }
            onDeclined:{
                addTimePopup.close();
            }
        }
    }
    Popup {
        id: editTimePopup
        width: root.width
        height: root.height
        modal: true
        dim: true
        focus: true
        background: Rectangle {
            color: Style.transparent
        }
        property int index: 0
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: EditTime {
            headerText: "Зміна часу"
            onAccepted: function(hE, mE, hD, mD) {
                console.log("editTimePopup::accepted", hE, mE, hD, mD)
                if(_roomController && _roomController.editableComponent){
                    console.log("editTimePopup::accepted", hE, mE, hD, mD)
                    _roomController.editableComponent.editTimePlan(editTimePopup.index, hE, mE, hD, mD)
                }

                editTimePopup.close();
            }
            onDeclined:{
                editTimePopup.close();
            }
        }
    }
}
