#include "AutoWindow.h"
#include "ui_AutoWindow.h"
#include <QFileDialog>
#include "AutoConfiguration.h"
#include "AutoCore/AutoComment.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), fileListModel( new QStringListModel()),
    folderListModel( new QStringListModel()), fileFolderListModel( new QStringListModel())
{
    ui->setupUi(this);

    ui->stackedWidget->setVisible( false );
    //    ui->adminDemoGroup->setVisible( false );

    showMaximized();

    connect( ui->addCustomStyleButton, SIGNAL(clicked()), ui->stackedWidget,SLOT(show()));
    connect( ui->addCustomStyleButton, SIGNAL(clicked()), ui->addCustomStyleButton,SLOT(hide()));

    connect( ui->doneButton, SIGNAL(clicked()), ui->stackedWidget,SLOT(hide()));
    connect( ui->doneButton, SIGNAL(clicked()), ui->addCustomStyleButton,SLOT(show()));

    connect( ui->stakedGotoBriefButton, SIGNAL(clicked()), this, SLOT(setStakedIndex()));
    connect( ui->stakedGotoParamButton, SIGNAL(clicked()), this, SLOT(setStakedIndex()));
    connect( ui->stakedGotoReturnButton, SIGNAL(clicked()), this, SLOT(setStakedIndex()));
    connect( ui->stakedGotoEndButton, SIGNAL(clicked()), this, SLOT(setStakedIndex()));
    connect( ui->doneButton, SIGNAL(clicked()), this, SLOT(setStakedIndex()));

    // Tab 1
    connect( ui->addFilesButton, SIGNAL(clicked()), this, SLOT(addFiles()));
    connect( ui->applyOnFilesButton, SIGNAL(clicked()), this, SLOT(applyCommentsOnSelectedFiles()));

    // Tab2
    connect( ui->addFolderButton, SIGNAL(clicked()), this, SLOT(addFolder()));


    // Tab4 : Preview
    connect( ui->browsePreviewFileButton, SIGNAL(clicked()), this, SLOT(browseFileNLoadForPreview()));
    connect( ui->applyOnPreviewButton, SIGNAL(clicked()), this, SLOT(applyNLoadForPreview()));
    connect( ui->selectNapplyOnFileButton, SIGNAL(clicked()), this, SLOT(applyNLoadForPreviewFile()));


    // Tab5 : Demo
    connect( ui->demoEditCheckBox, SIGNAL(toggled(bool)), this, SLOT(makeDemoEditable(bool)));


    fileList = AutoConfiguration::readConfiguration( "Files" ).toStringList();
    folderList = AutoConfiguration::readConfiguration( "Folders" ).toStringList();

    fileListModel->setStringList(fileList);
    folderListModel->setStringList(folderList);
    fileFolderListModel->setStringList(fileList+folderList);

    ui->fileListView->setModel(fileListModel);
    ui->folderListView->setModel(folderListModel);
    ui->fileFolderListView->setModel(fileFolderListModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStakedIndex()
{
    if(sender() == ui->stakedGotoBriefButton)
    {
        ui->stackedWidget->setCurrentIndex( 1 );
    }
    if(sender() == ui->stakedGotoParamButton)
    {
        ui->stackedWidget->setCurrentIndex( 2 );
    }
    if(sender() == ui->stakedGotoReturnButton)
    {
        ui->stackedWidget->setCurrentIndex( 3 );
    }
    if(sender() == ui->stakedGotoEndButton)
    {
        ui->stackedWidget->setCurrentIndex( 4 );
    }
    if(sender() == ui->doneButton)
    {
        ui->stackedWidget->setCurrentIndex( 0 );
    }
}

void MainWindow::addFiles()
{
    QStringList files = QFileDialog::getOpenFileNames( this, "Add File/Files", "", "*" );
    foreach( QString file, files )
    {
        if( !fileList.contains( file ))
        {
            fileList.append( file );
        }
    }
    fileListModel->setStringList(fileList);
    fileFolderListModel->setStringList(fileList+folderList);

    ui->fileListView->setModel(fileListModel);
    ui->fileFolderListView->setModel(fileFolderListModel);
}

void MainWindow::addFolder()
{
    QString folder = QFileDialog::getExistingDirectory( this, "Add Folder" );
    if( ! folder.isEmpty())
    {
        if( !folderList.contains( folder ))
        {
            folderList.append( folder );
            //           fileListModel->setStringList( fileList );
        }
    }
    folderListModel->setStringList(folderList);
    fileFolderListModel->setStringList(fileList+folderList);

    ui->folderListView->setModel(folderListModel);
    ui->fileFolderListView->setModel(fileFolderListModel);
}

void MainWindow::browseFileNLoadForPreview()
{
    QString filePath = QFileDialog::getOpenFileName( this, "Browse File", "", "*" );

    //////////////////////////
    //    QString filePath = QApplication::applicationFilePath() + ".txt";
    //////////////////////////

    ui->previewFilePathLabel->setText( filePath );


    if( !filePath.isEmpty() && QFile::exists(filePath) )
    {
        QFile previewFile(filePath);
        if( previewFile.open( QFile::ReadOnly))
        {
            ui->previewInPutFileEdit->setText( previewFile.readAll());
        }
    }
}

void MainWindow::applyNLoadForPreview()
{
    QString previewIPText = ui->previewInPutFileEdit->toPlainText();

    //////////////////////////
    QString filePath = QApplication::applicationFilePath() + ".txt";
    if( !filePath.isEmpty() && QFile::exists(filePath) )
    {
        QFile previewFile(filePath);
        if( previewFile.open( QFile::WriteOnly))
        {
            previewFile.write( QByteArray().insert(0, previewIPText)  );
        }
    }
    //////////////////////////


    if( false == previewIPText.isEmpty() )
    {
        AutoComment object;
        previewIPText = object.applyCommentsOnText(previewIPText);
        ui->previewOutPutFileEdit->setText( previewIPText );
    }
}

void MainWindow::applyNLoadForPreviewFile()
{
    QString filePath = QFileDialog::getOpenFileName( this, "Browse File", "", "*" );
    ui->previewFilePathLabel->setText( filePath );

    if( !filePath.isEmpty() && QFile::exists(filePath) )
    {
        QFile previewFile(filePath);
        if( previewFile.open( QFile::ReadOnly))
        {
            ui->previewInPutFileEdit->setText( previewFile.readAll());
        }
    }

    QString previewIPText = ui->previewInPutFileEdit->toPlainText();

    //////////////////////////
    if( !filePath.isEmpty() && QFile::exists(filePath) )
    {
        QFile previewFile(filePath);
        if( previewFile.open( QFile::WriteOnly))
        {
            previewFile.write( QByteArray().insert(0, previewIPText)  );
        }
    }
    //////////////////////////


    if( false == previewIPText.isEmpty() )
    {
        AutoComment object;
        object.set_filePath( filePath );
        object.applyCommentsOnFile();

        if( !filePath.isEmpty() && QFile::exists(filePath) )
        {
            QFile modiFile(filePath);
            if( modiFile.open( QFile::ReadOnly))
            {
                ui->previewOutPutFileEdit->setText( modiFile.readAll());
            }
        }

        ui->previewOutPutFileEdit->setText( previewIPText );
    }
}

void MainWindow::makeDemoEditable(bool flag)
{
    ui->demoInPutTextEdit->setReadOnly( !flag );
}

void MainWindow::applyCommentsOnSelectedFiles()
{

}
