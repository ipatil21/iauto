#include "MainScreen.h"
#include "ui_mainscreen.h"
#include <QSettings>


using namespace std;

MainScreen::MainScreen(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainScreen), fileListModel( new QStringListModel())
{
    qDebug()<<Q_FUNC_INFO;
    ui->setupUi(this);

    fileList = readConfiguration( "Files" ).toStringList();
    fileListModel->setStringList(fileList);
    ui->listView->setModel(fileListModel);
}

MainScreen::~MainScreen()
{
    qDebug()<<Q_FUNC_INFO;
    delete ui;
}

QVariant MainScreen::readConfiguration( QString tag )
{
    QVariant retVal;
    QSettings settings( QCoreApplication::applicationDirPath() + "/Config.ini", QSettings::IniFormat );

    if( "Files" == tag )
    {
        settings.beginGroup( "APP_DATA" );
        retVal = settings.value( tag );
        settings.endGroup();
    }
    return retVal;
}

void MainScreen::writeConfiguration( QString tag, QVariant value )
{
    QSettings settings( QCoreApplication::applicationDirPath() + "/Config.ini", QSettings::IniFormat );
    if( "Files" == tag )
    {
        settings.beginGroup( "APP_DATA" );
        settings.setValue( tag, value );
        settings.endGroup();
    }
}

void MainScreen::on_addFilesButton_clicked()
{
    qDebug()<<Q_FUNC_INFO;
    QString filePath = QFileDialog::getOpenFileName( 0, "Select Files",  "" );    
    if( ! filePath.isEmpty())
    {
       if( !fileList.contains( filePath ))
       {
           fileList.append( filePath );
           fileListModel->setStringList( fileList );
       }
    }
}

void MainScreen::on_addFolderButton_clicked()
{
    qDebug()<<Q_FUNC_INFO;
}

void MainScreen::on_cancelButton_clicked()
{
    qDebug()<<Q_FUNC_INFO;

    writeConfiguration( "Files", fileList );

    exit(0);
}

void MainScreen::on_runButton_clicked()
{
    qDebug()<<Q_FUNC_INFO;

    QList<QListWidgetItem*> items;
    QStringList fileList;
    foreach (QListWidgetItem* item, items) {
        fileList.append( item->text());
    }

    AutoComment* pAutoComment = new AutoComment();

    pAutoComment->applyComments();

    foreach (QString filePath, fileList)
    {
        //AutoComment obj(filePath);
    }
}

