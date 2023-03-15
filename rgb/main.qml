import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import tdd.project 1.0

Window {
    id: root
    width: 1024
    height: 720
    visible: true
    title: qsTr("Hello World")

    RGBSimpleBackend {
        id: backend
    }

    ColumnLayout {
        anchors.fill: parent

        Item {
            height: 50
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignTop
            Layout.margins: 25

            TextField {
                id: filePathTextField
                Layout.fillWidth: true
                placeholderText: qsTr("Путь к файлу")
                readOnly: true
            }

            Button {
                height: 50
                width: 100
                text: qsTr("Открыть файл")
                onClicked: openFileDialog.open()
            }
        }

        Rectangle {
            color: "transparent"
            border.color: "black"
            Layout.alignment: Qt.AlignCenter
            height: 418
            width: 615

            Image {
                id: simpleImage
                source: backend.simpleImage
                anchors.fill: parent

            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    FileDialog {
        id: openFileDialog
        title: "Please choose a file"
        selectMultiple: false
        onAccepted: {
            filePathTextField.placeholderText = openFileDialog.fileUrl
            backend.openByteArrayFile(openFileDialog.fileUrl)
        }
    }
}


