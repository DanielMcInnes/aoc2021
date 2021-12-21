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

	/*
	Rectangle {
	color: "red"
	//opacity: modelData / 10
	border.color: "white"
	border.width: 1
	width: 20
	height: width
}*/
	ListView {
		id: view

		anchors.fill: parent
		delegate: Rectangle {
			color: "red"
			//opacity: modelData / 10
			border.color: "white"
			border.width: 1
			width: 20//columns.height
			height: width
			Component.onCompleted: console.log(Object.keys(modelData))
		}

		/*
			ListView {
			width: parent.width
			height: 20
			model: modelData
			orientation: ListView.Horizontal
			delegate: Rectangle {
				color: "red"
				//opacity: modelData / 10
				border.color: "white"
				border.width: 1
				width: 20//columns.height
				height: width
				Text {
					anchors.fill: parent
					text: modelData
				}
			}*/
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
			mapData.push(JSON.parse(JSON.stringify(data)))
			console.log("data:", data, data.length, mapData.length, "mapData[0]:", mapData[0])
			data.length = 0
			y++
			x = 0
		}

		for (var i = 0; i < mapData.length; ++i) {
			console.log("mapData[", i, "] =", mapData[i])
		}

		console.log(mapData.length)
		view.model = mapData
	}
}
