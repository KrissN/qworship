import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: tabLive

    Rectangle {
        id: columnLeft
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: dp(24)
        anchors.rightMargin: dp(12)

        Rectangle {
            id: lyricsSearchContainer
            border.color: colorPreviewBkgnt
            border.width: 1
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: lyricsSearch.height + 4

            TextInput {
                id: lyricsSearch
                x: 2
                y: 2
                focus: true
                selectByMouse: true
                width: parent.width - 4

                onTextChanged: {
                    console.log(text);
                }
            }
        }

        Rectangle {
            id: lyricsListContainer
            border.color: colorPreviewBkgnt
            border.width: 1
            anchors.topMargin: dp(24)
            anchors.top: lyricsSearchContainer.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }

    Rectangle {
        id: columnRight
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: dp(24)
        anchors.leftMargin: dp(12)

        Rectangle {
            id: lyricsContainer
            border.color: colorPreviewBkgnt
            border.width: 1
            anchors.fill: parent
        }
    }
}