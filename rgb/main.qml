import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.0
import tdd.project 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")



    RGBSimpleBackend {
        id: backend
    }

    Button {
        height: 50
        width: 100
        text: qsTr("Click me")
        onClicked: backend.hello_from_QML();
    }
}
