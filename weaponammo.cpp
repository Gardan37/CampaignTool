#include <QStringList>

#include "store.h"
#include "weaponammo.h"

WeaponAmmo::WeaponAmmo(QString name)
{
    Store store;

    QStringList dataFields = store.weaponammo(name).split(";", QString::SkipEmptyParts);

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        properties.insert(dataField[0], dataField[1]);
    }
}
