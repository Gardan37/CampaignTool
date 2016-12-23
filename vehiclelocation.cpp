#include "vehiclelocation.h"

VehicleLocation::VehicleLocation(QString propertyString)
{
    QStringList propertyList = propertyString.split(";", QString::SkipEmptyParts);

    for (int field = 0; field < propertyList.count(); field++)
    {
        QStringList propertyField = propertyList[field].split("=", QString::SkipEmptyParts);

        properties.insert(propertyField[0], propertyField[1]);
    }
}

int VehicleLocation::location()
{
    if(properties.contains("location"))
    {
        return properties.value("location").toInt();
    }

    return 0;
}

// private funtions
int VehicleLocation::critslotamount()
{
    int location = properties.value("location").toInt();

    if (location == VehicleLocation::H || 
        location == VehicleLocation::RL ||
        location == VehicleLocation::LL) 
    {
        return 6;
    }

    return 12;
}
