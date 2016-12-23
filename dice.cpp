#include <QtGlobal>
#include <QTime>

#include "dice.h"

bool Dice::seeded = false;

Dice::Dice(int die)
{
    if (!seeded)
    {
        qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
        seeded = true;
    }

    this->die = die;

}

int Dice::roll(int dices, int modifier)
{
    int result = modifier;

    for (int i=0; i < dices ; i++)
    {
        result += 1 + qrand() % die;
    }

    return result;
}
