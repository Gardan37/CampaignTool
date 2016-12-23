
#include "mapnode.h"
#include "mapstore.h"
//#include "store.h" TODO transfer btmstore to store

MapNode::MapNode()
{
    nodeType = MapNode::StrategicMap;
    nodeLocation = QPoint(0,0);
    parentNode = 0;
    this->nodeData.insert("display", "RootNode");
    children = QHash<QPair<int, int>, MapNode * >();
}

MapNode::MapNode(QMap<QString, QVariant>data, MapNode *parent)
{
    this->nodeData = data;
    this->parentNode = parent;

    if (this->nodeData.contains("type"))
    {
        this->nodeType = (MapNode::Type)nodeData.value("type").toInt();
    } else
    {
        this->nodeType = MapNode::StrategicMap;
    }

    if (this->nodeData.contains("location"))
    {
        QStringList values = this->nodeData.value("location").toString().split(",");
        this->nodeLocation = QPoint(values.at(0).toInt(), values.at(1).toInt());
    } else
    {
        this->nodeLocation = QPoint(0,0);
    }

    if (this->nodeType == MapNode::StrategicMapNode)
    {
        if (!this->nodeData.contains("contour"))
        {
            this->nodeData.insert("contour", "0");
        }
        if (!this->nodeData.contains("vegetation"))
        {
            this->nodeData.insert("vegetation", "0");
        }
        if (!this->nodeData.contains("water"))
        {
            this->nodeData.insert("water", "0");
        }
    }

    updateDisplayStr();

}

MapNode::MapNode(QString filename)
{
    this->nodeType = MapNode::StrategicMap;
    this->nodeLocation = QPoint(0,0);
    this->parentNode = 0;
    this->nodeData.insert("display", "RootNode");
    this->children = QHash<QPair<int, int>, MapNode * >();

    int stra_rows = 0;
    int stra_cols = 0;
    int tact_rows = 4;
    int tact_cols = 4;

    QMap<int, QString> mapNodes;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList nodes = in.readAll().split(QString("\n"), QString::SkipEmptyParts);

    for (int number = 0; number < nodes.count(); number++)
    {
        QMap<QString, QVariant> data = parseNodeStr(nodes[number]);
        int type = data.value("type").toInt();
        int id=1000000;
        int i=10000;
        int j=100;
        int ti=0;
        int tj=0;
        
        if (type == MapNode::StrategicMapNode)
        {
            QStringList values = data.value("location").toString().split(",");
            int row = values.at(0).toInt();
            int column =  values.at(1).toInt();
            i *= row;
            j *= column;

            if (stra_rows < row+1)
            {
                stra_rows = row+1;
            }
            if (stra_cols < column+1)
            {
                stra_cols = column+1;
            }
        } else //(type == MapNode::TacticalMapNode)
        {
            QStringList values = data.value("parentlocation").toString().split(",");
            i *= values.at(0).toInt();
            j *= values.at(1).toInt();
            values = data.value("location").toString().split(",");
            ti = 10* values.at(0).toInt();
            tj = values.at(1).toInt();
        }
        id = id*type+i+j+ti+tj;
        mapNodes.insert(id, nodes[number]);
    }
    
    file.close();

    for (int i=0; i<stra_rows; i++)
    {
        for (int j=0; j<stra_cols; j++)
        {
            int id=1000000+i*10000+j*100;
            QString nodeStr = mapNodes.value(id);
            
            QMap<QString, QVariant> dataStra = parseNodeStr(nodeStr);
            if (!dataStra.contains("type"))
            {
                dataStra.insert("type", MapNode::StrategicMapNode);
            }
            MapNode *strategicNode = new MapNode(dataStra, this);
            this->setChild(QPoint(i,j), strategicNode);
            
            for (int ti=0; ti<tact_rows; ti++)
            {
                for (int tj=0; tj<tact_cols; tj++)
                {
                    int tid=1000000+id+ti*10+tj;
                    nodeStr = mapNodes.value(tid);
                    
                    QMap<QString, QVariant> dataTact = parseNodeStr(nodeStr);
                    if (!dataTact.contains("type"))
                    {
                        dataTact.insert("type", MapNode::TacticalMapNode);
                    }
                    MapNode *tacticalNode = new MapNode(dataTact, strategicNode);
                    strategicNode->setChild(QPoint(ti,tj), tacticalNode);
                }
            }
        }
    }

}

MapNode::~MapNode()
{
}

MapNode::Type MapNode::type()
{
    return nodeType;
}

QPoint MapNode::location()
{
    return nodeLocation;
}

QVariant MapNode::data(QString key)
{
    if (!nodeData.contains(key))
    {
        return QVariant();
    }
    return nodeData.value(key);
}

MapNode *MapNode::child(QPoint childLocation)
{
    if (children.contains(qPointToPair(childLocation)))
    {
        return children.value(qPointToPair(childLocation));
    }

    return 0;
}

MapNode *MapNode::parent()
{
    return parentNode;
}

void MapNode::setLocation(QPoint location)
{
    this->nodeLocation = location;
}

void MapNode::setData(QString key, QVariant value)
{
    nodeData.insert(key, value);

    if (key == "contour" || key == "vegetation" || key == "water" || key == "mapname")
    {
        updateDisplayStr();
    } 
}

void MapNode::setChild(QPoint location, MapNode *child)
{
    child->setLocation(location); // make sure that coordinates are coherent
    children.insert(qPointToPair(location), child);

    if (nodeType == MapNode::StrategicMap)
    {
        int childX = location.x();
        int childY = location.y();

        if (childX > nodeLocation.x())
        {
            nodeLocation.setX(childX);
        } 
        if (childY > nodeLocation.y())
        {
            nodeLocation.setY(childY);
        } 
    }
}

int MapNode::rowCount()
{
    switch (nodeType) {
    case StrategicMap:
        return nodeLocation.x()+1;
        break;
    case TacticalMap:
        return 4;
        break;
    case BattleTechMap:
        break;
    default:
        break;
    }

    return 0; 
}

int MapNode::columnCount()
{
    switch (nodeType) {
    case StrategicMap:
        return nodeLocation.y()+1;
        break;
    case TacticalMap:
        return 4;
        break;
    case BattleTechMap:
        break;
    default:
        break;
    }

    return 0;
}

int MapNode::childCount()
{
    return children.count();
}

QString MapNode::toString()
{
    QString nodeStr;

    nodeStr.append(QString("%1=%2;").arg("type").arg(nodeData.value("type").toString()));
    if (nodeData.value("type").toInt() == MapNode::TacticalMapNode)
    {
        nodeStr.append(QString("%1=%2;").arg("parentlocation").arg(nodeData.value("parentlocation").toString()));
    }
    nodeStr.append(QString("%1=%2;").arg("location").arg(nodeData.value("location").toString()));

    QMapIterator<QString, QVariant> i(nodeData);
    while (i.hasNext())
    {
        i.next();
        if (!(QString("type").compare(i.key()) == 0 || 
              QString("parentlocation").compare(i.key())  == 0 || 
              QString("location").compare(i.key()) == 0))
        {
            nodeStr.append(QString("%1=%2;").arg(i.key()).arg(i.value().toString()));
        }
    }

    return nodeStr;
}

QMap<QString, QVariant> MapNode::parseNodeStr(QString nodeStr)
{
    QMap<QString, QVariant> data;

    int position = 0;
    while (position < nodeStr.length())
    {
        if (nodeStr.mid(position, 1) != " ")
            break;
        position++;
    }

    nodeStr = nodeStr.mid(position).trimmed();
    if (nodeStr.isEmpty())
    {
        return data;
    }

    QStringList dataFields = nodeStr.split(";", QString::SkipEmptyParts);

    for (int field = 0; field < dataFields.count(); field++)
    {
        int fieldposition = 0;

        while (fieldposition < dataFields[field].length())
        {
            if (dataFields[field].mid(fieldposition, 1) != " ")
                break;
            fieldposition++;
        }
        QStringList dataField = dataFields[field].mid(fieldposition).trimmed().split("=", QString::SkipEmptyParts);

        data.insert(dataField[0], dataField[1]);
    }

    return data;
}



void MapNode::generateTacticalMap()
{
    if (nodeType != MapNode::StrategicMapNode || children.count() > 0) 
    {
        return;
    }

    int contour = nodeData.value("contour").toInt();;
    int vegetation = nodeData.value("vegetation").toInt();;

    MapStore *store = new MapStore();
    for (int ti=0; ti<rowCount(); ti++)
    {
        for (int tj=0; tj<columnCount(); tj++)
        {
            QString tag = store->getMapTag(contour, vegetation); //, 1000*ti+5000*tj);
            QMap<QString, QVariant> dataMap;
            dataMap.insert("type", MapNode::TacticalMapNode);
            dataMap.insert("parentlocation", QString("%d,%d").arg(nodeLocation.x()).arg(nodeLocation.y()));
            dataMap.insert("location", QString("%d,%d").arg(ti).arg(tj));
            dataMap.insert("tag", tag);
            dataMap.insert("mapname", store->getMapName(tag));
            this->setChild(QPoint(ti,tj), new MapNode(dataMap, this));
        }
    }
}

void MapNode::save(QString fileName)
{
    if (nodeType != MapNode::StrategicMap)
    {
        return;
    }

    int stra_rows = nodeLocation.x();
    int stra_cols = nodeLocation.y();
    int tact_rows = 4;
    int tact_cols = 4;
    QMap<int, QString> mapNodes;

    for (int i=0; i<stra_rows; i++)
    {
        for (int j=0; j<stra_cols; j++)
        {
            int id=1000000+i*10000+j*100;
            MapNode *strategicNode = child(QPoint(i,j));
            QString nodeStr = strategicNode->toString();
            mapNodes.insert(id, nodeStr);

            for( int ti=0; ti<tact_rows; ti++)
            {
                for (int tj=0; tj<tact_cols; tj++)
                {
                    int tid=1000000+id+ti*10+tj;
                    nodeStr = strategicNode->child(QPoint(ti,tj))->toString();
                    mapNodes.insert(tid, nodeStr);
                }
            }
        }
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "couldn't open file for writing";
    } else
    {
        QTextStream out(&file);
        QMapIterator<int, QString> i(mapNodes);
        while (i.hasNext())
        {
            i.next();
            out << i.value() << "\n";
        }
        
        file.close();
    }
}

QPair<int, int> MapNode::qPointToPair(QPoint point)
{
    return QPair<int, int>(point.x(), point.y());
}

void MapNode::updateDisplayStr()
{
    QString displayStr = QString();

    if (nodeType == MapNode::StrategicMapNode)
    {
        displayStr = QString("C%1V%2W%3").arg(nodeData.value("contour").toString()).arg(nodeData.value("vegetation").toString()).arg(nodeData.value("water").toString());
    } else if (nodeType == MapNode::TacticalMapNode)
    {
        if (nodeData.contains("mapname"))
        {
            displayStr = nodeData.value("mapname").toString();
        } else {
            displayStr = QString("%1%2 (%3%4)").arg(QChar('A'+nodeLocation.x())).arg(nodeLocation.y()+1).arg(QChar('A'+parentNode->location().x())).arg(parentNode->location().y()+1);
        }
    }

    nodeData.insert("display", displayStr) ;
}

