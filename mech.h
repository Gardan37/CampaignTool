#ifndef MECH_H
#define MECH_H

#include <QtGui>
#include "mechlocation.h"

class Mech
{
public:
    Mech();
    ~Mech();

    void create(QString variant); // result is variant in factory condition
    void load(QString idString);        // load saved mech
    void save(); // ISSUE, how to get unique id's (in db table can handle it but in file..)

    QStringList toStringList();
    QString idString();

private:
    // QString: Name, Variant
    // int:
    //  Location (armorleft, armortotal, internalleft, internaltotal)
    //  - critlist
    //    - ammobins (currenttype, left, capacity)
    //  Heatlevel, techlevel
/*    14:05 <@Gardan> mech/lance sheet tarvitsee tiedot jokaiselle mechille: unitposition, boardposition, mwname, gunnery,
                    piloting, initiative, leadership(?), mwhealth .. mech: name,variant,tonnage,movements,
                    weaponlist(note #1), armor/internallists (#2), criticallists (#3), ammobinlist(#4), heat(note#5)
    14:05 <@Gardan> #1 ase, sijainti, heat, dam, min/short/medium/long range
    14:06 <@Gardan> #2 sisältää hitlocation rollin numerot 3 suunnasta, lukumäärä paljon on ehjänä, tilaa
                    damamerkinnöille
    14:07 <@Gardan> #3 yksinkertainen ruksittava numeroitu lista heittoja varten
    14:08 <@Gardan> #4 ase, loca, dama/round, rounds, tila tukkimiehenkirjanpidolle kulutuksesta
    14:09 <@Gardan> #5 tila kirjaamiselle, modit ja avoid heitot vois olla vain alalaidassa kaikille yhteisesti
    14:10 <@Gardan> .. kysymys kuuluu onko jotkut noista tiedoista sellaisia mitä ei juuri koskaan tarvita (voidaan
                    katsoa mastertaulukoista kirjasta/printistä)
    14:38 <@Gardan> .. weapons taulukko kyllä ei tarttis olla kuin ase+loca+heat (vikakin vain heat laskun
                    nopeuttamiseksi) .. kyl ne muut statit voi kattoa yhdestä taulukosta joka ei ole kovin iso meidän
                    teknolla
    14:40 <@Gardan> ups .. heatsinks kans tarttee olla

                lokaatio on kyllä ratkaisevampi joten tehdään lokaatiopohjainen (lokaatiolla on equja lista ja
                critpaikka_id:llä indeksoituna) ja equlista jolla on vaan lokaatio/crit_id jolla se paikan saa
                helposti

**/
    // General info
    // - Name, variant, tonnage, speed W/R/J, cost, BV, maintenance(cond), maplocation, status
    // Locations
    // - armor full (H,CT,CTr,RT,RTr,LT,LTr,RA,LA,RL,LL)
    // - armor damage (H,CT,CTr,RT,RTr,LT,LTr,RA,LA,RL,LL)
    // - internal damage (H,CT,RT,LT,RA,LA,RL,LL)
    // Crit loc list H: life support, sensors, cockpit, ,sensors, (empty), life support,
    //               T: 3 eng, 4 gyro, 3 eng, 2 (empty)
    //               LA/RA: Shoulder, upper arm actuator, lower arm actuator, hand actuator, 8 (empty)
    //               LT/RT: 12 (empty)
    //               LL/RL: Hip, upper arm actuator, lower arm actuator, hand actuator, 2 (empty) )
    // Fully destroyed engine 3, gyro 2, sensors 2, life support 1
    // Ammo bins (used, max)
    // Equipment list: OK
    // Heat: heatsinks, temperature

    // erikseen Equipments luokka, jossa tarkemmat
    // erikseen Equ store luokka, jossa ladattuna tiedot

    // general info + currnt unit info(damage, heat, mapLocation, ...)
    static int counter; // probably not working anymore .. see save/load

    QString idStr;
    QString name;
    QString variant;
    int tonnage;
    int heatsinks;
    int movement[3];
    QMap<int, MechLocation *> locations;// H,CT,RT,LT,RA,LA,RL,LL
    QMultiMap<QString, QString> equipments; // keys are AC2_2, AC2Ammo_2, Sensors_1, HS_8
                                            // values are "type=AC2", "ammo=40", "ammotype=normal", "status=jammed"
};

#endif // MECH_H
