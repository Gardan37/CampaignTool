#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QObject>
#include <QtGui>

class Equipment : public QObject
{
public:
    //static const int counter = 0;

    Equipment(QString name); // result is base equipment in factory condition

    int location();
    QList<int> getCritslots();
    QString toString();
    QString idString();

private:
    QString idStr;
    QMap<QString, QString> properties;
};

#endif // EQUIPMENT_H
