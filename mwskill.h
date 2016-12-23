#ifndef MWSKILL_H
#define MWSKILL_H

#include <QtGui>
#include "mw.h"

class Mw;

class MwSkill
{
public:
    MwSkill(QString data, Mw *mw);

    void changeXp(int xp);
    bool equals(QString name);

    QString name();
    int level();
    int xp();
    int tn();
    QString complexity();

private:
    Mw *mw;
    QString skillName;
    int levelCurrent;
    int xpExtra;

    QString complexityRating;
    QString linkAttribute1;
    QString linkAttribute2;

};
#endif // MWSKILL_H
