#ifndef MECHLOCATION_H
#define MECHLOCATION_H

#include <QtGui>

class MechLocation
{
public:
    enum locationId {H=1,CT,RT=3,LT,RA=5,LA,RL=7,LL,LOCATIONS};
    enum structureId {INTERNAL=0, FRONT, REAR, FULL=0, DAMAGE};
    // enum direction {Front=1, FrontRight, Right, Rear, Left, FrontLeft};

    MechLocation(int id, int tonnage);
    MechLocation(QString propertyString);

    int location();

    void setArmor(int front, int rear=-1);
    void setEquipment(QString equipmentId, QStringList equipmentslots);
    QString toString();

/*
    void setDamage(int damage, int direction = MechLocation::Front); //vai bool rear=false ?
    void modifyDamage(int damage);
    void doDamage(int damage); // can cause crits

    void damageCrit(int slot);
    void fixCrit(int slot);

*/
private:
    int critslotamount();

    int id;
    int structure[3][2]; // internal, front, rear .. Full, damage
    QMultiMap<int, QString> critslots; // int XY: slotXY (X=1,2 Y=1-6) .. QString equname or Hit status

    static int internaltable[17][MechLocation::LOCATIONS];
};

#endif // MECHLOCATION_H
