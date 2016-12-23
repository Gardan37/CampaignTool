#ifndef WEAPONAMMO_H
#define WEAPONAMMO_H

#include <QObject>
#include <QtGui>

class WeaponAmmo : public QObject
{
public:
    WeaponAmmo(QString name);

private:
    QMap<QString, QString> properties;

};

#endif // WEAPONAMMO_H
