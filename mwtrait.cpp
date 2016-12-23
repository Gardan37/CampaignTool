#include <QtGui>
#include "mwtrait.h"


MwTrait::MwTrait(QString data)
{
    QStringList dataFields = data.split(";", QString::SkipEmptyParts );
    QMap<QString, QString> dataMap;

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        dataMap.insert(dataField[0], dataField[1]);
    }

    this->traitName = dataMap.value("name");
    this->xpTotal = 0;
}

void MwTrait::changeXp(int xp)
{
    xpTotal += xp;
}

bool MwTrait::equals(QString name)
{
    if(traitName.compare(name) == 0)
    {
        return true;
    }

    return false;
}

QString MwTrait::name()
{
    return traitName;
}

// TODO this is trait dependable
int MwTrait::level()
{
    if (xpTotal < 0)
    {
        return int(xpTotal-99); // -200 - -101 means level -2. Check this
    }
    return int(xpTotal/100);
}

int MwTrait::xp()
{
    return xpTotal;
}

