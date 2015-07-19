import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    id: mainwindow
    title: "Main Window"
    visible: true
    width: 400
    height: 400

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
