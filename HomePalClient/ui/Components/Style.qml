pragma Singleton

import QtQuick 2.12

QtObject {
    id: style

    readonly property real pressedColorCoefficient: 1.2


    readonly property color darkRed: "#bf2026"
    readonly property color lightGrey: "#d9d9d9"
    readonly property color veryLightGrey: "#e6e6e6"
    readonly property color grey: "#7f7f7f"
    readonly property color semiTransparentGrey: "#337f7f7f"

    readonly property color darkGrey: "#353F47"
    readonly property color darkGreen: "#006c31"
    readonly property color orange: "#FFA500"
    readonly property color darkOrange: "#FF5400"
    readonly property color yellow: "yellow"
    readonly property color lightYellow: "#ffe698"
    readonly property color white: "#ffffff"
    readonly property color semiTransparentWhite: "#33ffffff";
    readonly property color black: "#000000"
    readonly property color transparent: "transparent"
    readonly property color lightBlue: "#bed7ef"
    readonly property color semiTransparentBlue: "#1A0081D4"
    readonly property color radialGrey: "#8a8a8a"
    readonly property color backgroundBlueLight: "#4E5C67"
    readonly property color backgroundBlue: "#1B2A37"
    readonly property color rose: "#ffdede"
    readonly property color cyanBlue: "#009AB2"

    readonly property color homeScreenGreen: "#0FB100"
    readonly property color semiTransparent: "#33000000"
    readonly property color semiTransparentPress: "#66111111"
    readonly property color green: "#0EAA00"
    readonly property color semiTransparentGreen: "#330EAA00"
    readonly property color red: "#E30613"
    readonly property color transparentRed: "#33E30613"
    readonly property color blue: "#0081D4"
    readonly property color semiTransparentOrange: "#33FFA500"
    readonly property color lightOrange: "#44F67511"

    readonly property int defaultRadius: 5
    readonly property int defaultWidth: 4

    readonly property string fontFamily: "Droid Sans"
    readonly property var fontMain: FontLoader { id: fontMainLoader; source: "../fonts/Koulen-Regular.ttf" }

    readonly property string bluetooth: "qrc:icons/bluetooth.png"
    readonly property string cross: "qrc:icons/cross.png"
    readonly property string trashcan: "qrc:icons/trashcan.png"
    readonly property string delay: "qrc:icons/delay.png"
    readonly property string edit: "qrc:icons/edit.png"
    readonly property string onoff: "qrc:icons/onoff.png"

    readonly property font fontHeader: Qt.font({
        family: fontFamily,
        weight: Font.Bold,
        pixelSize: 20
    });


    property font font: Qt.font({
        family: fontFamily,
    });
}
