#include "ossource.h"
#include "config.h"
#include "json.h"
#include "osinfo.h"

#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QMap>
#include <QMapIterator>

OsSource::OsSource(QObject *parent) :
    QObject(parent)
{
}

void OsSource::setSource(const char * type)
{
    source = type;
}

QString OsSource::getSource()
{
    return(source);
}

void OsSource::setDevice(const char * id)
{
    device = id;
}

QString OsSource::getDevice()
{
    return(device);
}

void OsSource::setLocation(const char * locn)
{
    location = locn;
}

QString OsSource::getLocation()
{
    return(location);
}

void OsSource::monitorDevice()
{
    qDebug() << "OsSource::monitorDevice";
}

void OsSource::monitorNetwork(QNetworkAccessManager *netaccess)
{
    qDebug() << "OsSource::monitorNetwork" << location;
}

void OsSource::clearOSes()
{
    oses.clear();
}

void OsSource::addOS(OsInfo *os, const QString source)
{
    QMap<QString,OsInfo *>::Iterator i = oses.find(os->name());
    if (i != oses.end())
    {   //Already exists
        //Check if new OS is newer
        //if ((existing_details["release_date"].toString() < new_details["release_date"].toString()) || (existing_details["source"].toString() == SOURCE_INSTALLED_OS))
        if ( (os->releaseDate() > i.value()->releaseDate()) || source == SOURCE_INSTALLED_OS)
            //replace with Newer OS.
            i.value() = os;
    }
    else
    {   //New OS
        oses[os->name()] = os;
    }

}