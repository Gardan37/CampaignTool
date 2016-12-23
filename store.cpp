#include "store.h"
#include "mech.h"

Store::Store()
{
}

QStringList Store::mechdataraw(QString variant)
{
    QFile file(QString("store/data/mech_%1.txt").arg(variant));
    if (!file.open(QIODevice::ReadOnly))
    {
        return QStringList();
    }

    QTextStream in(&file);
    QStringList mechList = in.readAll().split(QString("\n"), QString::SkipEmptyParts);

    return mechList;
}

QStringList Store::mechdata(QString idStr)
{
    QFile file(QString("store/mechs/%1.txt").arg(idStr));
    if (!file.open(QIODevice::ReadOnly))
    {
        return QStringList();
    }

    QTextStream in(&file);
    QStringList mechList = in.readAll().split(QString("\n"), QString::SkipEmptyParts);

    return mechList;
}

void Store::mechsave(QString idStr, QStringList mechList)
{
    QFile file(QString("store/mechs/%1.txt").arg(idStr));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "couldn't open file for writing";
    } else
    {
        QTextStream out(&file);
        for (int i = 0; i < mechList.size(); ++i)
        {
            out << mechList.at(i) << endl;
        }
        file.close();
    }
}

QStringList Store::vehicledata(QString variant)
{
    return QStringList(variant);
}

QStringList Store::characterdata(QString character)
{
    return QStringList(character);
}

QStringList Store::mapdata(QString mission)
{
    return QStringList(mission);
}

QString Store::equipment(QString name)
{
    return QString(name);
}

QString Store::weapon(QString name)
{
    return QString(name);
}

QString Store::weaponammo(QString name)
{
    return QString(name);
}

