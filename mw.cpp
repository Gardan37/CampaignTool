#include "mw.h"

// file
// attribute:name=BOD;xp=300

Mw::Mw(QString name, QString attributeData, QString skillData, QString traitData)
{
    this->mwname = name;

    //Attributes
    QStringList propertyList = attributeData.split(QString("\n"), QString::SkipEmptyParts );
    for (int property = 0; property < propertyList.count(); property++)
    {
        MwAttribute *attribute = new MwAttribute(propertyList[property]);
        attributes.insert(attribute->name(), attribute);
    }
    //Skills
    propertyList = skillData.split(QString("\n"), QString::SkipEmptyParts );

    for (int property = 0; property < propertyList.count(); property++)
    {
        MwSkill *skill = new MwSkill(propertyList[property], this);
        skills.insert(skill->name(), skill);
    }
    //Traits
    propertyList = traitData.split(QString("\n"), QString::SkipEmptyParts );

    for (int property = 0; property < propertyList.count(); property++)
    {
        MwTrait *trait = new MwTrait(propertyList[property]);
        traits.insert(trait->name(), trait);
    }
    healthData = QPair<int,int>(6, 6);
}

Mw::~Mw()
{

}

QString Mw::toString()
{
    return mwname;
}

void Mw::changeXpSkill(QString skill, int xp)
{
    skills.value(skill)->changeXp(xp);
}

void Mw::changeXpTrait(QString trait, int xp)
{
    traits.value(trait)->changeXp(xp);
}

void Mw::changeXpAttribute(QString attribute, int xp)
{
    attributes.value(attribute)->changeXp(xp);
}

int Mw::skill(QString skill)
{
    return skills.value(skill)->level();
}

int Mw::attribute(QString attribute)
{
    return attributes.value(attribute)->level();
}

int Mw::attributeBonus(QString attribute)
{
    return attributes.value(attribute)->bonus();
}

int Mw::trait(QString trait)
{
    return traits.value(trait)->level();
}

QString Mw::name()
{
    return mwname;
}

int Mw::gunneryB()
{
    return skills.value("gunnery/mech/ballistic")->level();
}

int Mw::gunneryL()
{
    return skills.value("gunnery/mech/laser")->level();
}

int Mw::gunneryM()
{
    return skills.value("gunnery/mech/missile")->level();
}

int Mw::gunnery()
{
    return skills.value("gunnery/mech")->level();
}

QString Mw::gunneryStr()
{
    if (skills.contains("gunnery/mech"))
    {
        return QString("%1/%1/%1").arg(gunnery());
    }
    return QString("%1/%2/%3").arg(gunneryB()).arg(gunneryL()).arg(gunneryM());
}

int Mw::piloting()
{
    return skills.value("piloting/mech")->level();
}

int Mw::initiative()
{
    return skills.value("tactics/land")->level();
}

int Mw::health()
{
    return healthData.first;
}

int Mw::hits()
{
    return healthData.second-healthData.first;
}

QString Mw::healthStr()
{
    return QString("%1/%2").arg(healthData.first).arg(healthData.second);
}
