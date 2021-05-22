#include <QApplication>
#include <qdebug.h>
#include "MainScreen.h"

int main(int argc, char *argv[])
{
    //qDebug()<<Q_FUNC_INFO;

    QApplication a(argc, argv);
    MainScreen w;
    w.show();

    return a.exec();
}
