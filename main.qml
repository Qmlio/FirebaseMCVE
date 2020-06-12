import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import Error 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Code Error")
    Database {
        id: db
        onCompleted: {
            console.log("set value finished ")
        }
    }
    Column {
        anchors.centerIn: parent
        spacing: 16
        Button {

            text: "sign in"
            onClicked: auth.signInAnnonymously()
        }
        Button {

            text: "set value"
            onClicked: {
                var value = {
                    name: "John Doe",
                    likes: 3
                }
                db.test(JSON.stringify(value))
            }
        }
    }
}
