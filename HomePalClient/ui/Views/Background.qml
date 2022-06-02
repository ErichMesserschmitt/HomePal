import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.2
import QtQuick.Dialogs
import "../Components"
import "../Views"

Item {


    ColumnLayout {
        anchors.fill: parent;
        spacing: 2
        Rectangle {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: Style.darkOrange
        }
        Rectangle {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: Style.orange
        }
        Rectangle {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: Style.lightGrey
        }
    }
}
