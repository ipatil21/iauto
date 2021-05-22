#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QDebug>
#include <QFile>

class FileHandler
{

public:
    FileHandler();
    ~FileHandler();

    bool open(QFile::OpenModeFlag mode);
    QByteArray readEveryLine();
    QByteArray readSingleLine();
    bool shrink(int shrink);
    bool grow(int shrink);
    QByteArray writeData(QByteArray &data);
    bool flush();
    void close();

//private:
    QFile* m_qtFile;
    //QByteArray m_readSingleLine;
};

#endif // FILEHANDLER_H
