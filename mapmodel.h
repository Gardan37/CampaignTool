#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractTableModel>
#include "mapnode.h"

class MapNode;

class MapModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MapModel(QObject *parent=0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void initMap(MapNode *dataNode);
    void setMap(MapNode::Type type, int row=0, int column=0);
    MapNode *root();

private:
    MapNode *getItem(const QModelIndex &index) const;

    MapNode *dataNode; // storage
    MapNode *rootNode; // active used by views
};

#endif // MAPMODEL_H
