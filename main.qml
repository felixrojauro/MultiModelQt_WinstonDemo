import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import CustomModel 1.0

Window {
    visible: true
    width: 300
    height: 200

    SingleModel {
        id: singleModel
    }
    MultiModel {
        id: multiModel
    }

    Rectangle {
        id: mainRec
        width:100
        height: parent.height
        border.color: "black"
        border.width: 2
        property int rowSpacing:3
        Flickable {
            id: flickBox
            anchors {left:parent.left; leftMargin:mainRec.rowSpacing; top:parent.top; topMargin:mainRec.rowSpacing;
                right:parent.right; rightMargin:mainRec.rowSpacing; bottom:parent.bottom; bottomMargin:mainRec.rowSpacing}
            clip: true
            flickableDirection: Flickable.VerticalFlick
            contentHeight: mainColumn.height

            Column {
                id: mainColumn
                width: parent.width
                spacing: mainRec.rowSpacing

                Row {
                    Text {text: "Data from Model 1"}
                }
                Repeater {
                    id: model1Repeater
                    //model: model1             // works with QML model defined below
                    //model: singleModel        // works with singleModel
                    model: multiModel.model1    // Want this to work as a singleModel
                    delegate: DataRow2 {
                        height: 20;
                        width: parent.width
                        typeText: type
                        valueText: value
                        isBlue: colorTest
                    }
                }

                Row {
                    Text {text: "Data from Model 2"}
                }
                Repeater {
                    id: model2Repeater
                    model: model2               // works with QML model
                    //model: multiModel.model2  // Want this to work!!
                    delegate: DataRow2 {
                        height: 20;
                        width: parent.width
                        typeText: type
                        valueText: value
                        isBlue: colorTest
                    }
                }
            }
        }
    }

    ListModel {
        id: model1
        ListElement {
            type: "m1 prop1"
            value: 1
            colorTest: true
        }
        ListElement {
            type: "m1 prop2"
            value: 2
            colorTest: true
        }
        ListElement {
            type: "m1 prop3"
            value: 3
            colorTest: true
        }
        ListElement {
            type: "m1 prop4"
            value: 4
            colorTest: true
        }
        ListElement {
            type: "m1 prop5"
            value: 5
            colorTest: true
        }
    }
    ListModel {
        id: model2
        ListElement {
            type: "m2 prop1"
            value: 11
            colorTest: false
        }
        ListElement {
            type: "m2 prop2"
            value: 22
            colorTest: false
        }
        ListElement {
            type: "m2 prop3"
            value: 33
            colorTest: false
        }
        ListElement {
            type: "m2 prop4"
            value: 44
            colorTest: false
        }
        ListElement {
            type: "m2 prop5"
            value: 55
            colorTest: false
        }
    }
}
