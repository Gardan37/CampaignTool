#include "mech.h"
#include "store.h"

int Mech::counter = 0;

Mech::Mech()
{
}

Mech::~Mech()
{
}
/**
 * Prereq:
 *  variant for searching from database 
 * Always same:
 *  engine: CT 11,12,13,22,23,24 + 10 heat sinks
 *  gyro: CT 14,15,16,21
 *  sensors: H 12,15
 *  life support: H 11 16
 *  cockpit: H 13
 *  shoulder: RA 11 LA 11
 *  upper arm act: RA 12 LA 12
 *  lower arm act: RA 13 LA 13   might be removed
 *  hand act: RA 14 LA 14        might be removed
 *  hip: RL 11 LL 11
 *  upper leg act: RL 12 LL 12
 *  lower leg act: RL 13 LL 13
 *  foot act: RL 14 LL 14
 * Required
 *  tonnage: provides internals, w/r movement with engine
 *  engine: size
 *  equipment: (equ,weapon,ammo) type, critslots
 *   heatsink: +1 heatsinks
 *   jumpjet: 0/0/+1 movement
 *
 *
 *
 * Equlista, tonnage, variant, name, 
 *
 *
 */

void Mech::create(QString variant)
{
    counter++;
    qDebug() << "Mech variant=" << variant << " counter=" <<counter;
    Store store;

    QStringList mechdata = store.mechdataraw(variant);

    QStringList dataFields = mechdata[0].split(";", QString::SkipEmptyParts);
    QMap<QString, QString> dataMap;

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        dataMap.insert(dataField[0], dataField[1]);
    }

    this->idStr = QString("mech_%1_%2").arg(variant).arg(counter);

    this->name = dataMap.value("name");
    this->variant = dataMap.value("variant");
    this->tonnage = dataMap.value("tonnage").toInt();
    this->heatsinks = dataMap.value("heatsinks").toInt();
    this->movement[0] = 0;
    this->movement[1] = 0;
    this->movement[2] = 0;

    for (int mechfield = 1; mechfield < MechLocation::LOCATIONS; mechfield++)
    {
        MechLocation *newLocation = new MechLocation(mechfield, this->tonnage);

        this->locations.insert(newLocation->location(), newLocation);
    }

    for (int field = 1; field < mechdata.size(); field++)
    {
        QStringList equFields = mechdata[field].split(";", QString::SkipEmptyParts);
        bool hasCrits = false;

        for (int equfield = 1; equfield < equFields.size(); equfield++)
        {
            this->equipments.insert(equFields[0], equFields[equfield]);
            if (equFields[equfield].startsWith("loc="))
            {
                hasCrits = true;
            }
        }

        if (hasCrits)
        {
            int loc = equFields.filter("loc").at(0).split("=").at(1).toInt();

            locations.value(loc)->setEquipment(equFields[0],equFields.filter("crit").replaceInStrings("crit=",""));
        }

        if (equFields[0].startsWith("Engine"))
        {
            int enginesize = equFields.filter("size").at(0).split("=").at(1).toInt();
            movement[0] = (int)(enginesize/tonnage);
            movement[1] = (int)(movement[0]*1.5);
        }

        if (equFields[0].startsWith("JumpJet"))
        {
            movement[2]++;
        }

        if (equFields[0].startsWith("Armor"))
        {
            int armor;
            int armorRear;

            armor = equFields.filter("H=").replaceInStrings("H=","").at(0).toInt();
            locations.value(MechLocation::H)->setArmor(armor);
            armor = equFields.filter("CT=").replaceInStrings("CT=","").at(0).split("/").at(0).toInt();
            armorRear = equFields.filter("CT=").replaceInStrings("CT=","").at(0).split("/").at(1).toInt();
            locations.value(MechLocation::CT)->setArmor(armor, armorRear);
            armor = equFields.filter("ST=").replaceInStrings("ST=","").at(0).split("/").at(0).toInt();
            armorRear = equFields.filter("ST=").replaceInStrings("ST=","").at(0).split("/").at(1).toInt();
            locations.value(MechLocation::RT)->setArmor(armor, armorRear);
            locations.value(MechLocation::LT)->setArmor(armor, armorRear);
            armor = equFields.filter("A=").replaceInStrings("A=","").at(0).toInt();
            locations.value(MechLocation::RA)->setArmor(armor);
            locations.value(MechLocation::LA)->setArmor(armor);
            armor = equFields.filter("L=").replaceInStrings("L=","").at(0).toInt();
            locations.value(MechLocation::RL)->setArmor(armor);
            locations.value(MechLocation::LL)->setArmor(armor);
        }
    }
}


// This is straightforward as all is stored currently
void Mech::load(QString idString)
{
    Store store;

    qDebug() << "Mech idStr=" << idString ;

    QStringList mechdata = store.mechdata(idString); // 0 is general data and 1-8 are locations data
                                                     // 9 is equipments (includes weapons)

    QStringList dataFields = mechdata[0].split(";", QString::SkipEmptyParts);
    QMap<QString, QString> dataMap;

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        dataMap.insert(dataField[0], dataField[1]);
    }

    this->idStr = idString;

    this->name = dataMap.value("name");
    this->variant = dataMap.value("variant");
    this->tonnage = dataMap.value("tonnage").toInt();
    this->heatsinks = dataMap.value("heatsinks").toInt();
    dataFields = dataMap.value("movement").split("/", QString::SkipEmptyParts);

    for (int movetype = 0; movetype < dataFields.count(); movetype++)
    {
        this->movement[movetype] = dataFields[movetype].toInt();
    }

    for (int mechfield = 1; mechfield < MechLocation::LOCATIONS; mechfield++)
    {
        MechLocation *newLocation = new MechLocation(mechdata[mechfield]);
        this->locations.insert(newLocation->location(), newLocation);
    }

    for (int mechfield = MechLocation::LOCATIONS; mechfield < mechdata.count(); mechfield++)
    {
        dataFields = mechdata[mechfield].split(";", QString::SkipEmptyParts);

        for (int field = 1; field < dataFields.count(); field++)
        {
            this->equipments.insert(dataFields[0], dataFields[field]);
        }
    }
}

void Mech::save()
{
    Store store;

    store.mechsave(idStr, toStringList());
}

QStringList Mech::toStringList()
{
    QStringList storeStringList;

    storeStringList << QString("type=mech;name=%1;variant=%2;tonnage=%3;heatsinks=%4;movement=%5/%6/%7").arg(name).arg(variant).arg(tonnage).arg(heatsinks).arg(movement[0]).arg(movement[1]).arg(movement[2]);

    for (int field = 1; field < MechLocation::LOCATIONS; field++)
    {
        storeStringList << locations.value(field)->toString();
    }

    // MedLaser_1;type=MedLaser;loc=2;crit=26

    QList<QString> keys = equipments.uniqueKeys();
    for (int key = 0; key < keys.size(); key++)
    {
        QString equipment = keys.at(key);
        QList<QString> values = equipments.values(equipment);

        for (int i = 0; i < values.size(); ++i)
        {
            equipment.append(";").append(values.at(i));
        }
        storeStringList << equipment;
    }

    return storeStringList;
}

QString Mech::idString()
{
    return idStr;
}
