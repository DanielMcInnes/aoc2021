#ifndef MAP_H
#define MAP_H


#include <QObject>
#include <QMap>
#include <QMetaType>
#include <QPoint>
#include <vector>

using namespace std;

enum Direction {
	Up,
	Left,
	Down,
	Right
};

class Position : public QPoint
{
public:
	Position(int x, int y, int risk) : QPoint(x, y), risk(risk) { }
	int risk;
};

const vector<Direction> directions{Up, Left, Down, Right};

class Path : public vector <Position>
{
public:
	int risk = 0;

	void addPosition(const Position point)
	{
		push_back(point);
		risk += point.risk;
	}

};

class Paths : public vector<Path>
{

};

typedef QMap<int, QMap<int, int> > MapData;

Q_DECLARE_METATYPE(MapData)

class Map : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QStringList data READ data WRITE setData NOTIFY dataChanged)


public:
	explicit Map(QObject *parent = nullptr);
	void setData(const QStringList& data)
	{
		_data = data;
		emit dataChanged();
	}
	QStringList data() const
	{
		return _data;
	}

	int width = 0;
	int height = 0;
	Position startPos;
	Position endPos;
	QStringList _data;
	MapData _mapData;

	Position getNextPoint(const Map& map, const Position currentPoint, const Direction direction)
	{
		Position retval(currentPoint);

		switch (direction)
		{
		case Up:
			retval.setY(retval.ry() - 1);
			break;
		case Left:
			retval.setX(retval.rx() - 1);
			break;
		case Right:
			retval.setX(retval.rx() + 1);
			break;
		case Down:
			retval.setY(retval.ry() + 1);
			break;
		}

		return retval;
	}

signals:
	void dataChanged();
	void mapDataChanged();

public slots:
};
#endif // MAP_H
