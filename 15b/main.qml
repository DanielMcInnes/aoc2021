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
	property var bestPath

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
	function cloneNode(node) {
		var newNode = {
			risk: 1,//node.risk,
			visited: false,//node.visited,
			cumulativeRisk: 2,//node.cumulativeRisk,
			from: [0,0]//node.from
		}
		return newNode
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
		console.log("mapContainsPoint: ", point)
		if ((point[0] < 0) || point[1] < 0) {
			console.log("mapContainsPoint: false")
			return false;
		}
		if ((point[0] >= mapWidth) || point[1] >= mapHeight) {
			console.log("mapContainsPoint: false")
			return false;
		}
		if (!!map[point[0]] && !!map[point[0]][point[1]]) {
			console.log("mapContainsPoint: true")
			return true
		}
		return false;
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
	function visitNode(node) {
		if (node.visited || !node || !node[0] || !map[node[0]]) {
			console.log("Already visited this node!")
			return
		}
		var oldPos = map[node[0]][node[1]]

		for (var i = 0; i < directions.length; ++i) {
			var direction = directions[i]
			var newPos = movePoint(node, direction)
			if (mapContainsPoint(newPos)) {

				console.log("visitNode [", node.toString(), "]: direction:", directionsStrings[direction],
							"newPos:", newPos[0], newPos[1], "map[node[0]][node[1]].risk:", map[node[0]][node[1]].risk)
				console.log("mapWidth:", mapWidth)
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

		readonly property int cellSize: 30
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
				color: "red"//pathContainsLocation(bestPath, xy) ? "green" : "red"
				opacity: /*pathContainsLocation(bestPath, xy) ? 1 :  */modelData.risk / 10
				border.color: "black"
				border.width: 1
				width: xview.cellSize
				height: xview.cellSize
				Column {
					anchors.centerIn: parent
					Text {
						text: modelData.risk
					}
					/*
					Text {
						text: modelData.cumulativeRisk
					}
					*/
					/*
					Text {
						text: modelData.from.toString()
					}*/
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
			for (var i = 0; i < 5; ++i) {
				for (var key2 in line) {
					var risk = parseInt(line[key2]) + i
					risk = risk > 9 ? risk - 9 : risk
					var node = {
						risk: risk,
						visited: false,
						cumulativeRisk: -1,
						from: [-1,-1]
					}
					data.push(node)
				}
			}
			mapData.push(cloneArray(data))
			data.length = 0
		}
		var mapDataLength = mapData.length
		for (var i = 0; i < 4; ++i) {
			for (var j = 0; j < mapDataLength; ++j) {
				var line = cloneArray(mapData[j])
				for (var k = 0; k < line.length; ++k) {
					var node = line[k]
					var risk = node.risk + i + 1
					risk = risk > 9 ? risk - 9 : risk
					line[k].risk = risk
				}
				mapData.push(line)
			}
		}

		mapData[0][0].cumulativeRisk = 0
		mapData[0][0].from = [0,0]

		for (var i = 0; i < mapData.length; ++i) {
			var line = mapData[i]
			var string = ""
			for (var j = 0; j < line.length; ++j) {
				var node = line[j]
				string += node.risk
			}

			console.log("mapData[", i, "]:", string)
		}

		map = mapData
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
