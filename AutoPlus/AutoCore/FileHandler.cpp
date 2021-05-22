#include "FileHandler.h"

FileHandler::FileHandler()
{
    qDebug()<<Q_FUNC_INFO;
    m_qtFile = new QFile();
    m_qtFile->setFileName("/home/uidr6217/1.txt");//filePath);
}

FileHandler::~FileHandler()
{
    qDebug()<<Q_FUNC_INFO;
    m_qtFile->close();
}

bool FileHandler::open(QFile::OpenModeFlag mode)
{
    bool isfileOpen = m_qtFile->open(mode);
    qDebug()<<Q_FUNC_INFO<<"isfileOpen :"<<isfileOpen;
    return isfileOpen;
}

QByteArray FileHandler::readEveryLine()
{
    return m_qtFile->readAll();
}

QByteArray FileHandler::readSingleLine()
{
    QByteArray readSingleLine = m_qtFile->readLine();
    return readSingleLine;
}

bool FileHandler::grow(int grow)
{
    return m_qtFile->resize(grow);
}

bool FileHandler::shrink(int shrink)
{
    return m_qtFile->resize(shrink);
}

bool FileHandler::flush()
{
    return m_qtFile->flush();
}

void FileHandler::close()
{
    return m_qtFile->close();
}

QByteArray FileHandler::writeData(QByteArray &data)
{
    m_qtFile->write(data);
}
