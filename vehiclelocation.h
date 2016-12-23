#ifndef VEHICLELOCATION_H
#define VEHICLELOCATION_H

#include <QtGui>
class VehicleLocation
{
public:
    enum locationId {H=1,CT,RT,LT,RA,LA,RL,LL,LOCATIONS};
    //enum locationProperty { ArmorFront=1, ArmorRear, Internal};
    // enum direction {Front=1, FrontRight, Right, Rear, Left, FrontLeft};

    VehicleLocation(QString propertyString);

    int location();
/*
    void setDamage(int damage, int direction = VehicleLocation::Front); //vai bool rear=false ?
    void modifyDamage(int damage);
    void doDamage(int damage); // can cause crits

    void damageCrit(int slot);
    void fixCrit(int slot);

*/
private:
    int critslotamount();

    QMap<QString, QString> properties; // armor, armorRear, internal
                                       // damArmor, damArmorRear, damInternal
                                       // location, critslotXY (
};

#endif // VEHICLELOCATION_H
