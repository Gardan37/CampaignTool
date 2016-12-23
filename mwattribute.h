#ifndef MWATTRIBUTE_H
#define MWATTRIBUTE_H

#include <QString>

class MwAttribute
{
public:
    MwAttribute(QString data);

    void changeXp(int xp);
    bool equals(QString name);

    QString name();
    int level();
    int xp();
    int bonus();

private:
    QString attributeName;
    int xpTotal;
};
#endif // MWATTRIBUTE_H  
