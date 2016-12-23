#ifndef DICE_H
#define DICE_H

#include <QObject>
#include <QtGui>



class Dice : public QObject
{
public:
    Dice(int die);
    int roll(int dices=1, int modifier=0);

private:
    static bool seeded;

    int die;
};

#define d2 Dice(2)
#define d6 Dice(6)
#define d10 Dice(10)
#define d20 Dice(20)

#endif // DICE_H
