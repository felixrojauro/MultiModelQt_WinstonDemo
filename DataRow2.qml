import QtQuick 2.0

Rectangle {
    id: dataRow
    property alias typeText: rowText.text
    property alias valueText: rowValue.text
    property bool isBlue: true
    color: isBlue ? "lightblue" : "orange"
    Row {
        spacing:5
        Text { id:rowText }
        TextInput { id:rowValue }
    }
}
