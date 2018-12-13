#include <QStringList>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <string.h>

#define USAGE "\n**Usage: ./ini_writer -f Test.ini Server/serverip=192.168.1.123 Local/localip=192.168.1.124 Local/localport=8080 ..."

int main( int argc, char *argv[] )
{
    if ( 3 > argc )
    {
        qDebug() << "**Input parameter(s) error!" << USAGE;

        return -1;
    }

    bool fileFlag = false;

    QString iniFileName( "" );
    QStringList arguments;
    arguments.clear();

    for ( int i = 1; i < argc; i++ )
    {
        if ( 0 == strcmp(argv[i], "-f") )
        {
            if ( i < (argc - 1) )
            {
                ++i;
                iniFileName = argv[i];
                fileFlag = true;

                continue;
            }
            else
            {
                break;
            }
        }

        arguments << argv[i];
    }

    if ( !fileFlag )
    {
        qDebug() << "**Please specified the configure file name through signatrue '-f'.";

        return -1;
    }

    if ( !QFile::exists(iniFileName) )
    {
        qDebug() << "**Can NOT find file named:" << iniFileName;

        return -1;
    }

    int added = 0, modified = 0, success = 0, failed = 0;

    QStringList value;
    QSettings setttings( iniFileName, QSettings::IniFormat );

    for ( int i = 0; i < arguments.count(); i++ )
    {
        value = arguments[i].split( '=' );

        if ( 2 == value.count() )
        {
            if ( setttings.contains(value[0]) )
            {
                modified++;
            }
            else
            {
                added++;
            }

            setttings.setValue( value[0], value[1] );

            success++;
        }
        else
        {
            failed++;
        }
    }

    qDebug() << "**[Done]: Added =" << added << ", Modified =" << modified;
    qDebug() << "          Success =" << success << ", Failed =" << failed;

    return 0;
}
