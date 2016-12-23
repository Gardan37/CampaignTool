#ifndef MWTRAIT_H
#define MWTRAIT_H

#include <QString>

class MwTrait
{
public:
    MwTrait(QString data);

    void changeXp(int xp);
    bool equals(QString name);

    QString name();
    int level();
    int xp();

private:
    QString traitName;
    int xpTotal;
};
#endif // MWTRAIT_H  
