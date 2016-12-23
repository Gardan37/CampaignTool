#include <QStringList>

#include "weapon.h"
#include "store.h"

Weapon::Weapon(QString name)
{
    //counter++;

    Store store;

    QStringList dataFields = store.weapon(name).split(";", QString::SkipEmptyParts);

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        properties.insert(dataField[0], dataField[1]);
    }

    //this->idStr = QString("Weapon%1").arg(counter);
}

QList<int> Weapon::getCritslots()
{
    QList<int> critslots;

    return critslots;
}

QString Weapon::toString()
{
    return QString("Not implemented");
}

QString Weapon::idString()
{
    return idStr;
}
