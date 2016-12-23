#include "vehicle.h"
#include "store.h"

Vehicle::Vehicle()
{


}

Vehicle::Vehicle(QString variant)
{
    this->variant = variant;

    Store store;

    QStringList vehicledata = store.vehicledata(variant); // 0 is general data and 1-8 are locations data

    QStringList dataFields = vehicledata[0].split(";", QString::SkipEmptyParts);
    QMap<QString, QString> dataMap;

    for (int field = 0; field < dataFields.count(); field++)
    {
        QStringList dataField = dataFields[field].split("=", QString::SkipEmptyParts);
        dataMap.insert(dataField[0], dataField[1]);
    }

    this->name = dataMap.value("name");
    this->variant = dataMap.value("variant"); // .equals(vehicleVariant);

    for (int field = 1; field < VehicleLocation::LOCATIONS; field++)
    {
        VehicleLocation *newLocation =  new VehicleLocation(vehicledata[field]);

        locations.insert(newLocation->location(), newLocation);
    }
}


Vehicle::~Vehicle()
{

}

QString Vehicle::toString()
{
    return QString("Not implemented");
}
