#include <QtGui>
#include "mapstore.h"
#include "dice.h"

MapStore::MapStore()
{
    createStore();
    createRandomTable();
}

void MapStore::createStore()
{
    //QFile file("/home/gardan/Qt4/Btech/CampaignTool/store/mapstore.txt");
    QFile file("store/mapstore.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList maps = in.readAll().split(QString("\n"), QString::SkipEmptyParts);

    for (int number = 0; number < maps.count(); number++)
    {
        QHash<QString, QVariant> data;
        QStringList dataFields = maps[number].split(";", QString::SkipEmptyParts);
        for (int field = 0; field < dataFields.count(); field++)
        {
            QStringList dataField = dataFields[field].trimmed().split("=", QString::SkipEmptyParts);
            data.insert(dataField[0], dataField[1]);
        }
        store.insert(data.value("tag").toString(), data.value("amount").toInt());
        mapNames.insert(data.value("tag").toString(), data.value("mapname").toString());
    }
}

void MapStore::createRandomTable()
{
    //QFile file("/home/gardan/Qt4/Btech/CampaignTool/store/mapsrandomtable.txt");
    QFile file("store/mapsrandomtable.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList rows = in.readAll().split(QString("\n"), QString::SkipEmptyParts);

    for (int row = 0; row < rows.count(); row++)
    {
        QStringList columns = rows[row].split(";", QString::SkipEmptyParts);
        for (int column = 0; column < columns.count(); column++)
        {
            randomTable.insert(QPair<int,int>(row, column), columns[column]);
        }
    }
}

QString MapStore::getMapTag(int contour, int vegetation)
{
    QString tag;

    if (vegetation < 0)
    {
        vegetation = 0;
    }

    do
    {
        int contour_roll = roll(contour);
        int vegetation_roll = roll(vegetation);
        tag = randomTable.value(QPair<int,int>(contour_roll, vegetation_roll));
    } while (store.value(tag) == 0);

    store.insert(tag, store.value(tag)-1);

    return tag;
}

QString MapStore::getMapName(QString tag)
{
    return mapNames.value(tag);
}

int MapStore::roll(int modifier)
{
    int roll;
    int dices;
    bool reroll;

    do
    {
        reroll = false;
        dices = d6.roll(2);
        roll = dices -1 +modifier*3;

        if (dices == 2 && roll > 1)
        {
            modifier -= 1;
            reroll = true;
        } else if (dices == 12 && roll < 20)
        {
            modifier += 1;
            reroll = true;
        }

        if (roll < 1)
        {
            roll = 1;
        } else if (roll > 20)
        {
            roll = 20;
        }
    } while (reroll);

    return roll;
}
