import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: tabItem

    states: [
        State {
            name: "visible"
            /*when: visible*/
            PropertyChanges { target: tabItem; opacity: 1.0 }
        },
        State {
            name: "hidden"
            /*when: !visible*/
            PropertyChanges { target: tabItem; opacity: 0.0 }
        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad; /*duration: 400; */}
    }
}