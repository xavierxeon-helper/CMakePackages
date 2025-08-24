import QtQuick
import QtQuick.Controls

Item
{
    Component
    {
        id: tableDelegate
        Rectangle
        {
            id: tableItem

            required property int row // provided by standard model
            required property int column // provided by standard model
            required property string name

            implicitWidth: 100
            implicitHeight: 30


            color: mouseArea.drag.active ? "lightblue" : "white"
            //border.color : "lightgray"
            z: mouseArea.drag.active ? 10 : 0

            Text
            {
                anchors.centerIn: parent

                text: name ? name : ""
                padding: 5
            }


            DropArea
            {
                id: dropArea

                anchors.fill: parent

                onDropped: function (drag)
                {
                    tabOrder.reOrder(drag.source.row,  drag.source.column, row, column);
                }
            }

            MouseArea
            {
                id: mouseArea

                anchors.fill: parent
                drag.target: tableItem
                onReleased: parent.Drag.drop()
            }

            Drag.active: mouseArea.drag.active
            Drag.source: tableItem
            Drag.hotSpot.x: tableItem.width / 2
            Drag.hotSpot.y: tableItem.height / 2
        }
    }

    HorizontalHeaderView
    {
        id: horizontalHeader

        anchors.left: tableView.left
        anchors.top: parent.top
        syncView: tableView
        clip: true

        textRole: "name"
    }

    TableView
    {
        id: tableView

        anchors.left: parent.left
        anchors.top: horizontalHeader.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true

        columnSpacing: 0
        rowSpacing: 0

        model: tabOrder
        delegate: tableDelegate
    }
}
