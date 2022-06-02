import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.2
import QtQuick.Dialogs
//import QtQuick.Controls
import "../Components"

AbstractButton {
    id: root;
    property color color: Style.white
    readonly property color realColor: root.pressed ? root.color === Style.semiTransparent ? Style.darkGrey : Qt.darker(root.color, 1.3) : root.color
    readonly property color realBorderColor: root.pressed ? Qt.darker(root.borderColor, 0.9) : root.borderColor
    property color textColor: Style.black
    property color borderColor: Style.grey
    property bool isHorizontal: true

    property int borderWidth: Style.defaultWidth
    property int radius: Style.defaultRadius

    property int fontSize: 20
    property var fontFamily: Style.fontMain.name

    property string image: ""

    Rectangle {
        anchors.fill: parent;
        border.width: root.borderWidth
        border.color: root.realBorderColor
        color: root.realColor
        radius: root.radius

        ColumnLayout {
            anchors.fill: parent;
            spacing: 0
            Item {
                Layout.fillHeight: true;
                Layout.fillWidth: true;
                visible: root.image.length > 0
                Image {
                    anchors.fill: parent;
                    anchors.margins: root.height * 0.2
                    sourceSize.width: width
                    fillMode: Image.PreserveAspectFit
                    source: root.image
                }
            }
            Text {
                Layout.fillHeight: false;
                Layout.preferredHeight: root.height * 0.3
                Layout.fillWidth: true;
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: root.textColor
                text: root.text
                visible: root.text.length > 0

                font.pointSize: root.fontSize
                font.family: root.fontFamily
                wrapMode: Text.WordWrap
                rotation: root.isHorizontal ? 0 : -90

            }
        }
    }
}
