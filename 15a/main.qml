import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import Foo 1.0
Window {
	visible: true
	visibility: "FullScreen"
	readonly property int up: 0
	readonly property int down: 1
	readonly property int left: 2
	readonly property int right: 3
	readonly property int mapWidth: map && map[0] ? map[0].length : 0
	readonly property int mapHeight: map ? map.length : 0
	readonly property var startPos: [0,0]
	readonly property var endPos: [mapWidth - 1, mapHeight - 1]
	property int counter: 0
	property var stringlist: Map.data
	property var map
	readonly property var directions: [down, right, left, up]
	property var path: []

	function branchPath(path) {
		console.log("starting from: ", path[path.length - 1])
		for (var i = 0; i < directions.length; ++i) {
			console.log("direction:", directions[i])
		}
	}

	ListView {
		id: xview

		anchors.fill: parent
		model: map
		delegate: ListView {
			property int xx : index
			width: parent.width
			height: 20
			model: modelData
			orientation: ListView.Horizontal
			delegate: Rectangle {
				property int yy : index
				color: "red"
				opacity: modelData / 10
				border.color: "white"
				border.width: 1
				width: 40//columns.height
				height: width
				Text {
					anchors.fill: parent
					text: modelData + "(" + xx + ","  + yy + ")"
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
			mapData.push(JSON.parse(JSON.stringify(data)))
			console.log("data:", data, data.length, mapData.length, "mapData[0]:", mapData[0])
			data.length = 0
			y++
			x = 0
		}


		for (var i = 0; i < mapData.length; ++i) {
			console.log("mapData[", i, "] =", mapData[i])
		}

		map = mapData
		console.log(mapData.length, "mapWidth:", mapWidth)
		path.push(startPos)
		branchPath(path)
	}
}
