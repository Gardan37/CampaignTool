#ifndef MAPSTORE_H
#define MAPSTORE_H

#include <QtGui>

class MapStore
{
public:
    MapStore();

    QString getMapTag(int contour, int vegetation);
    QString getMapName(QString tag);

private:
    void createStore();
    void createRandomTable();
    int roll(int modifier);

    QMap<QString, int> store;
    QHash<QPair<int, int>, QString> randomTable;
    QHash<QString, QString> mapNames;
};

#endif // MAPSTORE_H
