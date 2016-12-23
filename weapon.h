#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QtGui>

class Weapon : public QObject
{
public:
    //static const int counter = 0;

    Weapon(QString name); // result is base weapon in factory condition. If ammo weapon, single ammo bin included
    
    //TODO think how to organize these
    //WeaponAmmoType *ammo(QString type);
    //WeaponAmmoBin *ammoBin(); // returns new ammo bin object

    QList<int> getCritslots();
    QString toString();
    QString idString();

private:
    QString idStr;
    QMap<QString, QString> properties;

};

#endif // WEAPON_H
