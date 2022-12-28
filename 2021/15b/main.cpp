#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <QtQml/qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include <QVariant>
#include <QPoint>
#include <QMetaType>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctype.h>

#include "./map.h"
using namespace std;


void findAllPaths(Path path)
{
	/*
	for (auto direction : directions)
	{

	}
	*/
}

int main(int argc, char *argv[])
{
	static Map map;

	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;


	// allocate example before the engine to ensure that it outlives it
	QStringList stringList;
	Path path;

	string str;

	ifstream infile("data");
	while (infile >> str)
	{
		QString qs(str.c_str());
		stringList.append(qs);
		//cout << "str: " << str << " qs: " << qs.toStdString() << " count: " << stringList.count() << endl;
	}
	map.setData(stringList);

	qmlRegisterSingletonType<Map>("Foo", 1, 0, "Map", [](QQmlEngine*, QJSEngine*) -> QObject* {
		return &map;
	});
	//qmlRegisterType<MapData>("Foo", 1, 0, "MapData");

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
