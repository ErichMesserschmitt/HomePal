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
    property string headerText: "Devices List"
    signal accepted()
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
            RowLayout {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height * 0.15
                Layout.fillWidth: true;

                Rectangle {
                    Layout.fillHeight: true;
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
                CustomButton {
                    Layout.fillHeight: true;
                    Layout.fillWidth: false;
                    Layout.preferredWidth: height;
                    color: Style.white
                    textColor: Style.red
                    borderColor: Style.red
                    borderWidth: Style.defaultWidth
                    radius: Style.defaultRadius
                    onClicked: root.declined()
                    text: "X"
                    font.pixelSize: root.height * 0.15
                }
            }
            Flickable {
                id: flickableZone
                Layout.fillHeight: true;
                Layout.fillWidth: true;

                readonly property int columnSpacing: 2
                readonly property int proposedWidth: width
                readonly property int proposedHeight: root.height * 0.12
                property var components: _roomController.pendingComponents
                readonly property int itemsCount: components.length


                contentHeight: proposedHeight * itemsCount + ((itemsCount + 2) * columnSpacing)
                contentWidth: width

                flickableDirection: Flickable.VerticalFlick
                clip: true
                boundsBehavior: Flickable.StopAtBounds

                interactive: true

                ColumnLayout {
                    id: modulesGrid
                    anchors.fill: parent
                    spacing: 2
                    Repeater {
                        model: flickableZone.components
                        delegate: RowLayout {
                            CustomButton {
                                Layout.fillHeight: true;
                                Layout.fillWidth: true;
                                color: Style.lightGrey;
                                borderWidth: Style.defaultWidth
                                borderColor: Style.darkOrange
                                radius: Style.defaultRadius
                                enabled: false;
                                text: flickableZone.components[index].name /*+
                                      flickableZone.components[index].type === 1 ? "<br>On/Off switcher" :
                                      flickableZone.components[index].type === 2 ? "<br>Selectable value" : ""*/
                            }
                            CustomButton {
                                Layout.fillHeight: true;
                                Layout.fillWidth: false;
                                Layout.preferredWidth: height
                                color: Style.white;
                                borderWidth: Style.defaultWidth
                                borderColor: Style.green
                                radius: Style.defaultRadius
                                text: "OK"
                                onClicked: {
                                    _roomController.selectComponent(flickableZone.components[index].name, flickableZone.components[index].index, _roomController.selectedRoom)
                                    root.accepted();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
