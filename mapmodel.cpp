
#include "mapmodel.h"
#include "mapnode.h"

MapModel::MapModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void MapModel::initMap(MapNode *newDataNode)
{
    this->dataNode = newDataNode;
    this->rootNode = newDataNode;
    reset();
}

void MapModel::setMap(MapNode::Type type, int row, int column)
{
    if (type == MapNode::StrategicMap)
    {
        rootNode = dataNode;
    } else if (type == MapNode::TacticalMap)
    {
        rootNode = dataNode->child(QPoint(row,column));
    }
    reset();
}

int MapModel::rowCount(const QModelIndex &parent) const
{
    MapNode *node = getItem(parent);

    return node->rowCount();
}

int MapModel::columnCount(const QModelIndex &parent) const
{
    MapNode *node = getItem(parent);

    return node->columnCount();
}

QVariant MapModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (role == Qt::SizeHintRole)
    {
        return QSize(10, 10);
    }

    if (role == Qt::DisplayRole)
    {
        MapNode *node = rootNode->child(QPoint(index.row(), index.column()));
        return node->data("display");
    }

    if (role == Qt::ToolTipRole)
    {
        return QString("%1%2").arg(QChar('A'+index.row())).arg(1+index.column());
    }

    return QVariant();
}

QVariant MapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::SizeHintRole)
    {
        return QSize(20, 20);
    }

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            return QString().setNum(section+1,10);
        }
        if (orientation == Qt::Vertical)
        {
            return QString(QChar('A'+section));
        }
    }

    return QVariant();
}

MapNode *MapModel::root()
{
    return rootNode;
}

MapNode* MapModel::getItem(const QModelIndex &index) const
{
    if (index.isValid() )
    {
        MapNode* node = static_cast<MapNode*>(index.internalPointer());
        if (node)
        {
            return node;
        }
    }

    return rootNode;
}

