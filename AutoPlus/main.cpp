#include "AutoWindow.h"
#include <QApplication>
#include <QFile>
#include <QStyleFactory>

void readConfig()
{
    QString path;
    path = QCoreApplication::applicationDirPath() + "/qss/Win_Stone_Gray.qss";

    QString styleSheet;
    QFile file( path );
    bool isFileAvailable = file.open(QFile::ReadOnly);
    if(isFileAvailable)
        styleSheet = QLatin1String(file.readAll());
//        styleSheet;
    else {
//#if defined( Q_OS_WIN ) || defined( Q_OS_LINUX )
//        QFile file1( ":/qss/Win_Stone_Gray.qss" );
//#else
//        QFile file1( ":/qss/Mac_Stone_Gray.qss" );
//#endif
//        file1.open(QFile::ReadOnly);
//        styleSheet = QLatin1String(file1.readAll());
//        file1.close();
    }
    file.close();
//    if( isFileAvailable ){
//        QFileInfo fInfo( path );
//        QString iconPath = fInfo.absolutePath() + "/" + fInfo.completeBaseName();
//        styleSheet = styleSheet.replace( "CURRENT_QSS_ICONS_PATH", iconPath );
//    }

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    qApp->setStyleSheet(styleSheet);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    readConfig();

    MainWindow w;
    w.show();

    return a.exec();
}
