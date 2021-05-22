#ifndef AUTOCONFIGURATION_H
#define AUTOCONFIGURATION_H
#include <QSettings>

class AutoConfiguration
{
public:
    AutoConfiguration();
    static QVariant readConfiguration( QString tag );
    static void writeConfiguration( QString tag, QVariant value );

private:
    static QSettings settings;
};

#endif // AUTOCONFIGURATION_H
