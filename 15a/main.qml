import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import Foo 1.0
Window {
	visible: true
	visibility: "FullScreen"
	readonly property int up: 0
	readonly property int down: 0
	readonly property int left: 0
	readonly property int right: 0


	property int counter: 0
	property var stringlist: Map.data
	property var map

	readonly property var directions: [down, right, left, up]


/*
	ListView {
		id: view2

		anchors.fill: parent
		model: stringlist
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
*/
	ListView {
		id: view

		anchors.fill: parent
		delegate: ListView {
			id: columns
			width: parent.width
			height: 20
			orientation: ListView.Horizontal
			model: modelData
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
		var mapData = []
		var data = []
		var x = 0
		var y = 0

		for (var key in stringlist) {
			var line = stringlist[key]
			for (var risk in stringlist[key]) {
				data.push(line[risk])
				x++
			}
			mapData.push(data)
			console.log("data:", data, mapData.length)
			data.length = 0
			y++
			x = 0
		}
		map = mapData
		console.log(map.length)
		view.model = map
	}
}
