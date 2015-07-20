import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    id: mainwindow
    title: qsTr("Main Window")
    visible: true
    width: 400
    height: 400
    minimumWidth: 400
    minimumHeight: 400

    function dp(val) {
        return Math.round(val * (screenPixelDensity / 160));
    }

    property real uiClrHue: 80.0 / 360.0;
    property real uiClrVal: 0.9;
    property real uiSatMenu: 32.0 / 256.0;
    property real uiTrpMenu: 1.0;

    property color colorMenuBkgnd: Qt.hsla(uiClrHue, 1.0 - (uiSatMenu * (1.0 - uiClrVal)), 1 - uiSatMenu * 0.5, uiTrpMenu)

    Rectangle {
        id: topmenu
        width: parent.width
        height: dp(32)
        color: colorMenuBkgnd

        Rectangle {
            id: menuLive
        }
    }

    /*Rectangle {
        anchors.fill: parent

        Rectangle {
            width: 100
            height: 100
            x: 100
            y: 100
            color: "red"
            focus: true
            Keys.onPressed: {
                console.log("1");
            var m = transf.matrix;
            m.scale(1.0, 1.0);
                m.ortho(0.0, 1.0, 0.9, 0.1, 1.0, 1.0);
                transf.matrix = m;
                color = "green";
            }

            transform: Matrix4x4 {
                id: transf
                matrix: Qt.matrix4x4(0.98,  0.01,  0.01, 0,
                                     0.0,  0.98,  1.9e-16, 0,
                                     0.0,  -0.02,  1.0,  0.0,
                                     0.0,  0.0,  0.0,  1.0)
            }
        }
    }*/
}
