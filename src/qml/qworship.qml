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

    function mkColor(hue, val, sat, trp) {
        if (sat < 1.0) {
            val = 1.0 - (sat * (1.0 - val));
        }
        return Qt.hsla(hue, val, 1 - sat * 0.5, trp);
    }

    property real uiClrHue: 80.0 / 360.0;
    property real uiClrVal: 0.9;
    property real uiSatTabBkgnd: 32.0 / 256.0;
    property real uiTrpTabBkgnd: 1.0;
    property real uiSatTabText: 345.0 / 256.0;
    property real uiTrpTabText: 1.0;
    property real uiSatTabBkgndAct: 256.0 / 256.0;
    property real uiTrpTabBkgndAct: 1.0;

    property color colorTabBkgnd: mkColor(uiClrHue, uiClrVal, uiSatTabBkgnd, uiTrpTabText)
    property color colorTabText: mkColor(uiClrHue, uiClrVal, uiSatTabText, uiTrpTabText)
    property color colorTabItemBkgnd: mkColor(uiClrHue, uiClrVal, uiSatTabBkgnd, 0.0)
    property color colorTabItemBkgndHover: mkColor(uiClrHue, uiClrVal, uiSatTabBkgndAct, 1.0)
    property color colorTabItemBkgndActive: mkColor(uiClrHue, uiClrVal, uiSatTabBkgndAct, 0.6)

    ListModel {
        id: tabbarModel
        ListElement { label: qsTr("LIVE") }
        ListElement { label: qsTr("SEQUENCE") }
        ListElement { label: qsTr("LYRICS") }
        ListElement { label: qsTr("SETTINGS") }
    }

    Component {
        id: tabbarDelegate
        Rectangle {
            id: tabRect
            width: dp(240)
            height: dp(48)
            color: colorTabItemBkgnd

            MouseArea {
                id: mouseArea;
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    var oldIndex = tabRect.ListView.view.currentIndex;
                    tabRect.ListView.view.currentIndex = index;
                    tabObjects[oldIndex].state = "hidden";
                    tabObjects[oldIndex].z = 1.0;
                    tabObjects[index].state = "visible";
                    tabObjects[index].z = 2.0;
                }
            }

            Text {
                id: txt
                text: label
                font.pointSize: dp(20)
                anchors.centerIn: parent
                color: colorTabText
            }

            states: [
                State {
                    name: "hover"
                    when: (mouseArea.containsMouse)
                    PropertyChanges { target: tabRect; color: colorTabItemBkgndHover }
                }/*,
                State {
                    name: "active"
                    when: (tabbarView.currentItem ==  && !mouseArea.containsMouse)
                    PropertyChanges { target: tabRect; color: colorTabItemBkgndActive }
                }*/
            ]

            transitions: Transition {
                ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 200 }
            }
        }
    }

    Rectangle {
        id: tabbar
        width: parent.width
        height: dp(48)
        color: colorTabBkgnd

        ListView {
            id: tabbarView
            anchors.fill: parent

            model: tabbarModel
            delegate: tabbarDelegate

            orientation: ListView.Horizontal

            highlight: Rectangle {
                height: parent.height
                color: colorTabItemBkgndActive
            }
            highlightMoveVelocity: 2000.0
        }
    }

    Rectangle {
        id: content
        width: parent.width
        anchors.top: tabbar.bottom
        anchors.bottom: parent.bottom

        TabItem {
            id: tabLive
            anchors.fill: parent
            state: "visible"

            TabLive { id: tabLiveContent; anchors.fill: parent }
        }
        TabItem {
            id: tabSequence
            anchors.fill: parent
            state: "hidden"

            TabSequence { id: tabSequenceContent; anchors.fill: parent }
        }
        TabItem {
            id: tabLyrics
            anchors.fill: parent
            state: "hidden"

            TabLyrics { id: tabLyricsContent; anchors.fill: parent }
        }
        TabItem {
            id: tabSettings
            anchors.fill: parent
            state: "hidden"

            TabSettings { id: tabSettingsContent; anchors.fill: parent }
        }
    }

    property var tabObjects: [
        tabLive,
        tabSequence,
        tabLyrics,
        tabSettings
    ]

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
