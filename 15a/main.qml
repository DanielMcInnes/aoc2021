import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import Foo 1.0
Window {
	visible: true
	visibility: "FullScreen"

	property int counter: 0
	property var map: Map.data

	ListView {
		id: view2

		anchors.fill: parent
		model: map
		delegate: ListView {
			id: columns
			width: parent.width
			height: 20
			orientation: ListView.Horizontal
			model: modelData.split('')
			delegate: Rectangle {
				color: "red"
				opacity: modelData / 10
				border.color: "white"
				border.width: 1
				width: columns.height
				height: width
				Text {
					anchors.fill: parent
					text: modelData
				}
			}
		}
	}

	Component.onCompleted: {
		for (var key in map) {
			console.log("map[", key, "] =", map[key])
		}
	}
}
