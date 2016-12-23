#include <QStringList>

#include "equipment.h"
#include "store.h"

Equipment::Equipment(QString name)
{
    //counter++;

    Store store;

    QStringList dataFields = store.equipment(name).split(";", QString::SkipEmptyParts);

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        properties.insert(dataField[0], dataField[1]);
    }

    //this->idStr = QString("Equipment%1").arg(counter);

}

int Equipment::location()
{
    return properties.value("location").toInt();
}

QList<int> Equipment::getCritslots()
{
    QList<int> critslots;

    return critslots;
}

QString Equipment::toString()
{
    return QString("Not implemented");
}

QString Equipment::idString()
{
    return idStr;
}
