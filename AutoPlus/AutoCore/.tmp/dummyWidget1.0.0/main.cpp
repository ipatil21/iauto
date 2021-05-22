#include <QApplication>

#include <qdebug.h>
#include "MainScreen.h"

// Logics to add
// 1. Function overloading
// 2. void ; //Logic
// 3. classname::function name
// 4. structname
// 5. enum

int main(int argc, char *argv[])
{
    qDebug()<<Q_FUNC_INFO;

    QApplication a(argc, argv);
    MainScreen w;
    w.show();

    return a.exec();
}
