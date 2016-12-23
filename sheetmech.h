#ifndef LANCESHEET_H
#define LANCESHEET_H

#include <QObject>

class LanceSheet : public QObject
{
Q_OBJECT
public:
    explicit LanceSheet(QObject *parent = 0);

signals:

public slots:

};
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
*/
#endif // LANCESHEET_H
