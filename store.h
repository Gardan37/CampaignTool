#ifndef STORE_H
#define STORE_H

#include <QObject>
#include <QtGui>

// Role retrieve data from storages files, mysql ...

class Store : public QObject
{
public:
    Store();

    QStringList mechdataraw(QString variant);
    QStringList mechdata(QString idStr);
    void mechsave(QString idStr, QStringList mech);
    QStringList vehicledata(QString variant);
    QStringList characterdata(QString character);
    QStringList mapdata(QString mission);
    QString equipment(QString name);
    QString weapon(QString name);
    QString weaponammo(QString name);

};

#endif // STORE_H
