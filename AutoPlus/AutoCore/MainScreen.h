#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include "AutoComment.h"
#include <QStringListModel>

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();

private slots:
    void on_addFilesButton_clicked();
    void on_addFolderButton_clicked();
    void on_runButton_clicked();
    void on_cancelButton_clicked();

private:
    QVariant readConfiguration( QString tag );
    void writeConfiguration( QString tag, QVariant value );
    void saveBeforePowerOff(QString);
    void readAfterPowerOn();

    Ui::MainScreen *ui;
    QStringListModel *fileListModel;
    QStringList fileList;
};

#endif // MAINSCREEN_H
