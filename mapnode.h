#ifndef MAPNODE_H
#define MAPNODE_H

#include <QtGui>

class MapNode
{
public:
    // MapType describes level of Node represents.
    enum Type {StrategicMap=0, TacticalMap, BattleTechMap, StrategicMapNode=1, TacticalMapNode};

    MapNode();
    MapNode(QMap<QString, QVariant>data, MapNode *parent);
    MapNode(QString filename);
    ~MapNode();

    Type type();
    QPoint location();
    QVariant data(QString key);
    MapNode *child(QPoint location);
    MapNode *parent();

    void setLocation(QPoint location);
    void setData(QString key, QVariant value);
    void setChild(QPoint location, MapNode *child);

    int rowCount();
    int columnCount();
    int childCount();

    QString toString();
    void generateTacticalMap();
    void save(QString fileName);

private:
    QPair<int, int> qPointToPair(QPoint point);
    void updateDisplayStr();
    QMap<QString, QVariant> parseNodeStr(QString nodeStr);

    Type nodeType;
    QPoint nodeLocation;
    QMap<QString, QVariant> nodeData;
    MapNode *parentNode;
    QHash<QPair<int, int>, MapNode *> children;
};

#endif // MAPNODE_H
