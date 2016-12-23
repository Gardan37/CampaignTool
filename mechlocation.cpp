#include "mechlocation.h"

int MechLocation::internaltable[17][MechLocation::LOCATIONS] = {
    { 20, 3,  6,  5,  5,  3,  3,  4,  4},
    { 25, 3,  8,  6,  6,  4,  4,  6,  6},
    { 30, 3, 10,  7,  7,  5,  5,  7,  7},
    { 35, 3, 11,  8,  8,  6,  6,  8,  8},
    { 40, 3, 12, 10, 10,  6,  6, 10, 10},
    { 45, 3, 14, 11, 11,  7,  7, 11, 11},
    { 50, 3, 16, 12, 12,  8,  8, 12, 12},
    { 55, 3, 18, 13, 13,  9,  9, 13, 13},
    { 60, 3, 20, 14, 14, 10, 10, 14, 14},
    { 65, 3, 21, 15, 15, 10, 10, 15, 15},
    { 70, 3, 22, 15, 15, 11, 11, 15, 15},
    { 75, 3, 23, 16, 16, 12, 12, 16, 16},
    { 80, 3, 25, 17, 17, 13, 13, 17, 17},
    { 85, 3, 27, 18, 18, 14, 14, 18, 18},
    { 90, 3, 29, 19, 19, 15, 15, 19, 19},
    { 95, 3, 30, 20, 20, 16, 16, 20, 20},
    {100, 3, 31, 21, 21, 17, 17, 21, 21}
};

MechLocation::MechLocation(int id, int tonnage)
{
    this->id = id;

    switch (id) {
    case MechLocation::H :
        critslots.insert(11, "life support");
        critslots.insert(12, "sensors");
        critslots.insert(13, "cockpit");
        critslots.insert(15, "sensors");
        critslots.insert(16, "life support");
        break;
    case MechLocation::CT : 
        critslots.insert(11, "engine");
        critslots.insert(12, "engine");
        critslots.insert(13, "engine");
        critslots.insert(14, "gyro");
        critslots.insert(15, "gyro");
        critslots.insert(16, "gyro");
        critslots.insert(21, "gyro");
        critslots.insert(22, "engine");
        critslots.insert(23, "engine");
        critslots.insert(24, "engine");
        break;
    case MechLocation::RL : 
    case MechLocation::LL :
        critslots.insert(11, "hip");
        critslots.insert(12, "upper leg actuator");
        critslots.insert(13, "lower leg actuator");
        critslots.insert(14, "foot actuator");
        break;
    case MechLocation::RA : 
    case MechLocation::LA :
        critslots.insert(11, "shoulder");
        critslots.insert(12, "upper arm actuator");
        critslots.insert(13, "lower arm actuator");
        critslots.insert(14, "hand actuator");
        break;
    case MechLocation::RT : 
    case MechLocation::LT :
    default:
        break;
    }
    
    switch (id) {
    case MechLocation::H :
    case MechLocation::RL : 
    case MechLocation::LL :
    case MechLocation::RA : 
    case MechLocation::LA :
        structure[0][0] = internaltable[(int)((tonnage-20)/5)][id];
        structure[0][1] = 0;
        structure[1][0] = 0;
        structure[1][1] = 0;
        structure[2][0] = -1;
        structure[2][1] = 0;
        break;
    case MechLocation::CT : 
    case MechLocation::RT : 
    case MechLocation::LT :
    default:
        structure[0][0] = internaltable[(int)((tonnage-20)/5)][id];
        structure[0][1] = 0;
        structure[1][0] = 0;
        structure[1][1] = 0;
        structure[2][0] = 0;
        structure[2][1] = 0;
        break;
    }
}

MechLocation::MechLocation(QString propertyString)
{
    QStringList propertyList = propertyString.split(";", QString::SkipEmptyParts);

    QMap<QString, QString> properties;
    structure[0][0] = 0;
    structure[0][1] = 0;
    structure[1][0] = 0;
    structure[1][1] = 0;
    structure[2][0] = -1;
    structure[2][1] = 0;

    for (int field = 0; field < propertyList.count(); field++)
    {
        QStringList propertyField = propertyList[field].split("=", QString::SkipEmptyParts);

        if (propertyField[0] == "loc")
        {
            id = propertyField[1].toInt();
        } else if (propertyField[0].startsWith("slot"))
        {
            critslots.insert(propertyField[0].right(2).toInt(), propertyField[1]);
        } else
        {
            QString structureStr = propertyField[0].right(2);
            structure[structureStr.left(1).toInt()][structureStr.right(1).toInt()] = propertyField[1].toInt();
        }
    }
}

int MechLocation::location()
{
    return id;
}

void MechLocation::setArmor(int front, int rear)
{
    structure[MechLocation::FRONT][MechLocation::FULL] = front;
    if (rear >= 0)
    {
        structure[MechLocation::REAR][MechLocation::FULL] = rear;
    }
}

void MechLocation::setEquipment(QString equipmentId, QStringList equipmentslots)
{
    for (int field = 0; field < equipmentslots.size(); field++)
    {
        critslots.insert(equipmentslots.at(field).toInt(), equipmentId);
    }
}

QString MechLocation::toString()
{
    QString storeStr = QString("loc=%1").arg(id);
    int structureslots;

    if (structure[MechLocation::REAR][MechLocation::FULL] < 0)
    {
        structureslots = 2;
    } else
    {
        structureslots = 3;
    }

    for (int i=0; i<structureslots; i++)
    {
        for (int j=0; j<2; j++)
        {
            storeStr.append(QString(";structure%1%2=%3").arg(i).arg(j).arg(structure[i][j]));
        }
    }

    QMapIterator<int, QString> slotiter(critslots);
    while (slotiter.hasNext()) {
        slotiter.next();
        storeStr.append(QString(";slot%1=%2").arg(slotiter.key()).arg(slotiter.value()));
    }

    return storeStr;
}

// private funtions
int MechLocation::critslotamount()
{

    if (id == MechLocation::H ||
        id == MechLocation::RL ||
        id == MechLocation::LL)
    {
        return 6;
    }

    return 12;
}
