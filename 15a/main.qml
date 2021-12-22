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
	readonly property var directionsStrings: ["down", "right", "left", "up"]
	property var path: [[0,0]]

	function clone(thing) {
		return JSON.parse(JSON.stringify(thing))
	}

	function movePoint(point, direction) {
		var newPos = JSON.parse(JSON.stringify(point))
		switch (direction) {
		case up:
			newPos[1]--
			break;
		case down:
			newPos[1]++
			break;
		case left:
			newPos[0]--
			break;
		case right:
			newPos[0]++
			break;
		}
		return newPos
	}
	function mapContainsPoint(point) {
		if ((point[0] < 0) || point[1] < 0) return false;
		if ((point[0] >= mapWidth) || point[1] >= mapHeight) return false;
		return true
	}
	function canAddPointToPath(path, point) {
		if (pathContainsLocation(path, point)) return false
		return mapContainsPoint(point)
	}
	function branchPath(path) {
		var lastPos = path[path.length - 1]
		console.log("starting from: ", lastPos)
		for (var i = 0; i < directions.length; ++i) {
			var direction = directions[i]
			var newPos = movePoint(lastPos, direction)
			console.log("direction:", directionsStrings[direction], "newPos:", newPos, "lastPos:", lastPos)
			if (canAddPointToPath(path, newPos)) {

			}
		}
	}
	function pathContainsLocation(path, location) {
		for (var i = 0; i < path.length; ++i) {
			var loc = path[i]
			if (loc[0] === location[0] && loc[1] === location[1])  {
				return true
			}
		}
		return false
	}

	ListView {
		id: xview

		anchors.fill: parent
		model: map
		delegate: ListView {
			property int xx : index
			width: parent.width
			height: 60
			model: modelData
			orientation: ListView.Horizontal
			delegate: Rectangle {
				property int yy : index
				property var xy : [xx, yy]
				color: pathContainsLocation(path, xy) ? "green" : "red"
				opacity: pathContainsLocation(path, xy) ? 1 :  modelData / 10
				border.color: pathContainsLocation(path, xy) ? "black" : "white"
				border.width: pathContainsLocation(path, xy) ? 3 : 1
				width: 60
				height: 60
				Column {
					Text {
						text: modelData + "(" + xy + ")"
					}
					Text {
						text: path[0].join()
					}
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
		var loc = [0,10]
		console.log(mapData.length, "mapWidth:", mapWidth, mapContainsPoint(loc))
		branchPath(path)
	}
}
