#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setStakedIndex();
    void addFiles();
    void addFolder();

    void browseFileNLoadForPreview();
    void applyNLoadForPreview();
    void applyNLoadForPreviewFile();

    void makeDemoEditable(bool flag);

    void applyCommentsOnSelectedFiles();

private:
    Ui::MainWindow *ui;
    QStringList fileList;
    QStringList folderList;
    QStringListModel *fileListModel;
    QStringListModel *folderListModel;
    QStringListModel *fileFolderListModel;
};

#endif // MAINWINDOW_H
