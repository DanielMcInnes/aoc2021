import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import Foo 1.0
Window {
	id: root

	width: 640
	height: 480

	visible: true
	readonly property int up: 0
	readonly property int down: 1
	readonly property int left: 2
	readonly property int right: 3
	readonly property int mapWidth: map && map[0] ? map[0].length : 0
	readonly property int mapHeight: map ? map.length : 0
	readonly property var startPos: [0,0]
	readonly property var endPos: [mapWidth - 1, mapHeight - 1]
	property int pathCounter: 0
	property var stringlist: Map.data
	property var map
	readonly property var directions:			[down,	right,	left,	up]
	readonly property var directionsStrings:	["up","down","left","right"]
	property var path: [[0,0]]
	property var bestPath
	property var paths: []

	function cloneArray(thing) {
		return JSON.parse(JSON.stringify(thing))
	}
	function clonePath(path) {
		console.log("clonePath:", path.id, path.risk, path)
		var newPath = JSON.parse(JSON.stringify(path))
		newPath["id"] = path.id
		newPath["risk"] = path.risk
		return newPath
	}

	function movePoint(point, direction) {
		var newPos = cloneArray(point)
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
		//console.log("mapContainsPoint: ", point)
		if ((point[0] < 0) || point[1] < 0) {
			//console.log("mapContainsPoint: false")
			return false;
		}
		if ((point[0] >= mapWidth) || point[1] >= mapHeight) {
			//console.log("mapContainsPoint: false")
			return false;
		}
		//console.log("mapContainsPoint: true")
		return true
	}
	function totalRisk(path) {
		var risk = 0
		for (var i = 1; i < path.length; ++i) {
			var loc = path[i]
			risk += parseInt(map[loc[1]][loc[0]].risk)
		}
		path["risk"] = risk
		console.log(path.id, "totalRisk:", path.risk, "bestPath.risk:", bestPath.risk, (path.risk < bestPath.risk))
		if (!bestPath) {
			bestPath = clonePath(path)
			console.log("found first path", path.id, path.risk, path)
			console.log(JSON.stringify(path))
		}
		if (path.risk < bestPath.risk) {
			console.log(path.id, "new best path!", path.risk, path, path)
			bestPath = clonePath(path)
		}
	}
	function canAddPointToPath(path, point) {
		if (pathContainsLocation(path, point)) {
			return false
		}
		return mapContainsPoint(point)
	}
	function visitNode(node) {
		if (node.visited) {
			console.log("Already visited this node!")
			exit()
			return
		}
		var oldPos = map[node[0]][node[1]]

		for (var i = 0; i < directions.length; ++i) {
			var direction = directions[i]
			var newPos = movePoint(node, direction)
			if (mapContainsPoint(newPos)) {
				console.log(path.id, "visitNode [", node.toString(), "]: direction:", directionsStrings[direction], "newPos:", newPos, "map[node[0]][node[1]].risk:", map[node[0]][node[1]].risk)
				var mapLoc = map[newPos[0]][newPos[1]]
				var tentativeRisk = parseInt(mapLoc.risk) + parseInt(map[node[0]][node[1]].cumulativeRisk)
				if ((mapLoc.visited === false) &&
						((mapLoc.cumulativeRisk === -1) || tentativeRisk < mapLoc.cumulativeRisk)
						) {
					mapLoc.cumulativeRisk = tentativeRisk
					mapLoc.from = cloneArray(node)
					for (var key2 in mapLoc) {
						console.log("mapLoc[", key2, "]:", mapLoc[key2])
					}
				}
			}
		}
		oldPos.visited = true
	}
	function branchPath(path) {
		var lastPos = path[path.length - 1]
		for (var i = 0; i < directions.length; ++i) {
			var direction = directions[i]
			var newPos = movePoint(lastPos, direction)
			console.log(path.id, "direction:", directionsStrings[direction], "newPos:", newPos, "newPos.risk:", "lastPos:", lastPos)
			if (canAddPointToPath(path, newPos)) {
				var newPath = cloneArray(path)
				newPath.id = pathCounter++
				newPath.push(newPos)
				console.log("new path:", newPath.id,  newPath)
				paths.push(newPath)
				console.log("Paths:", paths.length)
				if (sameLocation(newPos, endPos)) { // we have reached the end
					totalRisk(newPath)
					console.log(newPath.id, "this path has reached the end", bestPath.risk, newPath.risk)
				} else {
					branchPath(newPath)
				}
			}
		}
		delete(path)
	}
	function sameLocation(loc1, loc2) {
		return (loc1[0] === loc2[0] && loc1[1] === loc2[1])
	}
	function pathContainsLocation(path, location) {
		for (var i = 0; i < path.length; ++i) {
			var loc = path[i]
			if (sameLocation(loc, location))  {
				return true
			}
		}
		return false
	}
	Timer {
		id: timer

		property var path
		interval: 0

	}


	ListView {
		id: xview

		readonly property int cellSize: 60
		anchors.fill: parent
		topMargin: 50
		leftMargin: 20
		//model: map
		delegate: ListView {
			property int yy : index
			width: parent.width
			height: xview.cellSize
			model: modelData
			orientation: ListView.Horizontal
			delegate: Rectangle {
				property int xx : index
				property var xy : [xx, yy]
				color: pathContainsLocation(bestPath, xy) ? "green" : "red"
				opacity: pathContainsLocation(bestPath, xy) ? 1 :  modelData.risk / 10
				border.color: pathContainsLocation(path, xy) ? "black" : "white"
				border.width: pathContainsLocation(path, xy) ? 3 : 1
				width: xview.cellSize
				height: xview.cellSize
				Column {
					anchors.centerIn: parent
					Text {
						text: modelData.risk
					}
					Text {
						text: modelData.cumulativeRisk
					}
					Text {
						text: modelData.from.toString()
					}
				}

			}
		}
	}
	Button {
		width: 100
		height: 50
		text: "start"
		onClicked: {
			console.log("starting...")
			for (var x = 0; x < mapWidth; ++x) {
				for (var y = 0; y < mapHeight; ++y) {
					visitNode([x,y])
				}
			}
			console.log("map[", mapWidth - 1, ",", mapHeight - 1, "].cumulativeRisk:", map[mapWidth - 1][mapHeight - 1].cumulativeRisk)
		}
	}
	Component.onCompleted: {
		var mapData = []
		var data = []

		for (var key in stringlist) {
			var line = stringlist[key]
			for (var key2 in line) {
				var risk = line[key2]
				var node = {
					risk: risk,
					visited: false,
					cumulativeRisk: -1,
					from: [-1,-1]
				}
				data.push(node)
			}
			mapData.push(cloneArray(data))
			data.length = 0
		}
		mapData[0][0].cumulativeRisk = 0
		mapData[0][0].from = [0,0]
		map = mapData
		path["id"] = 0
		path["risk"] = 1000000
		bestPath = clonePath(path)



		console.log("starting...")
		for (var x = 0; x < mapWidth; ++x) {
			for (var y = 0; y < mapHeight; ++y) {
				visitNode([x,y])
			}
		}
		console.log("map[", mapWidth - 1, ",", mapHeight - 1, "].cumulativeRisk:", map[mapWidth - 1][mapHeight - 1].cumulativeRisk)
		xview.model = map

		var from = cloneArray(map[mapWidth - 1][mapHeight - 1].from)
		bestPath.push([mapWidth-1, mapHeight - 1])

		while (sameLocation(from, [0,0]) === false) {
			//console.log("from:", from)
			bestPath.push(from)
			from = cloneArray(map[from[0]][from[1]].from)
		}
	}
}
