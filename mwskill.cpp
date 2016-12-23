#include "mwskill.h"
#include "mw.h"

MwSkill::MwSkill(QString data, Mw *mw)
{
    QStringList dataFields = data.split(";", QString::SkipEmptyParts );
    QMap<QString, QString> dataMap;

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        dataMap.insert(dataField[0], dataField[1]);
    }

    this->mw = mw;
    this->skillName = dataMap.value("name");
    this->levelCurrent = -1;
    this->xpExtra = 0;

    this->complexityRating = dataMap.value("complexityRating");
    this->linkAttribute1 = dataMap.value("link1");
    if (complexityRating.compare("CB") == 0 || complexityRating.compare("CA") == 0) 
    {
        this->linkAttribute2 = dataMap.value("link2");
    }
}

void MwSkill::changeXp(int xp)
{
    int target;
    int modifier = 10;

    xpExtra += xp;

    if (mw->trait("Learner") >= 3)
    {
        modifier = 9;
    } else if (mw->trait("Learner") <= -3)
    {
        modifier = 11;
    }

    target = (abs(levelCurrent)+1)*modifier;

    while (xpExtra >= target && levelCurrent <= 10)
    {
        levelCurrent++;
        xpExtra -= target;
        target = (levelCurrent+1)*modifier;
    }
}

bool MwSkill::equals(QString name)
{
    if(skillName.compare(name) == 0)
    {
        return true;
    }

    return false;
}

QString MwSkill::name()
{
    return skillName;
}

int MwSkill::level()
{
    return levelCurrent;
}

int MwSkill::xp()
{
    return xpExtra;
}

int MwSkill::tn()
{
    int tn = 8;

    if (complexityRating.compare("CA") == 0)
    {
        tn++;
    } else if (complexityRating.compare("SB") == 0)
    {
        tn--;
    }

    tn -= mw->attributeBonus(linkAttribute1);
    if (complexityRating.compare("SA") == 0 || complexityRating.compare("CA") == 0) 
    {
        tn -= mw->attributeBonus(linkAttribute2);
    }

    tn -= levelCurrent;
    return tn;
}

QString MwSkill::complexity()
{
    return complexityRating;
}

