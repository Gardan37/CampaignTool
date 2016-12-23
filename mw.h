#ifndef MW_H
#define MW_H

#include <QtGui>
#include "mwskill.h"
#include "mwtrait.h"
#include "mwattribute.h"

class MwSkill;

class Mw
{
public:
    Mw(QString name, QString attributeData, QString skillData, QString traitData);
    ~Mw();

    QString toString();

    void changeXpSkill(QString skill, int xp);
    void changeXpTrait(QString trait, int xp);
    void changeXpAttribute(QString attribute, int xp);

    // Time of War statistics getters
    int skill(QString skill);
    int attribute(QString attribute);
    int attributeBonus(QString attribute);
    int trait(QString trait);

    // BattleTech helper getters
    QString name();
    int gunneryB();
    int gunneryL();
    int gunneryM();
    int gunnery();
    QString gunneryStr(); // in format B/L/M
    int piloting();
    int initiative();
    int health();
    int hits();
    QString healthStr();

private:
    QString mwname;
    QMap<QString, MwSkill *> skills;
    QMap<QString, MwTrait *> traits;
    QMap<QString, MwAttribute *> attributes;
    QPair<int,int> healthData;
};

#endif // MW_H
