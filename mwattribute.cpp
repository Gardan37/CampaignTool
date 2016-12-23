#include <QtGui>
#include "mwattribute.h"

MwAttribute::MwAttribute(QString data)
{
    QStringList dataFields = data.split(";", QString::SkipEmptyParts);
    QMap<QString, QString> dataMap;

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        dataMap.insert(dataField[0], dataField[1]);
    }

    this->attributeName = dataMap.value("name");
    this->xpTotal = dataMap.value("xp").toInt();
}

void MwAttribute::changeXp(int xp)
{
    xpTotal += xp;
}

bool MwAttribute::equals(QString name)
{
    if(attributeName.compare(name) == 0)
    {
        return true;
    }

    return false;
}

QString MwAttribute::name()
{
    return attributeName;
}

int MwAttribute::level()
{
    return int(xpTotal/100);
}

int MwAttribute::xp()
{
    return xpTotal % 100;
}

int MwAttribute::bonus()
{
    int level = int(xpTotal/100);

    if(level == 0) 
    {
        return -4;
    } else if(level == 1) 
    {
        return -2;
    } else if(level >= 2 && level <= 10)
    {
        return int((level-4)/3);
    } else if(level >= 11 && level <= 14)
    {
        return int(level/3);
    }

    return 5;

}
