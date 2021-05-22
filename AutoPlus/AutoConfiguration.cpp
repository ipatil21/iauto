#include "AutoConfiguration.h"
#include <QCoreApplication>

QSettings AutoConfiguration::settings( QCoreApplication::applicationDirPath() + "/Config.ini", QSettings::IniFormat );
AutoConfiguration::AutoConfiguration()
{
}

QVariant AutoConfiguration::readConfiguration( QString tag )
{
    QVariant retVal;
    if( "Files" == tag )
    {
        settings.beginGroup( "APP_DATA" );
        retVal = settings.value( tag );
        settings.endGroup();
    }
    return retVal;
}

void AutoConfiguration::writeConfiguration( QString tag, QVariant value )
{
    if( "Files" == tag )
    {
        settings.beginGroup( "APP_DATA" );
        settings.setValue( tag, value );
        settings.endGroup();
    }
}
