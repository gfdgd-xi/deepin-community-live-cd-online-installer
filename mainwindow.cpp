#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStorageInfo>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include "diskcontrol.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置程序标题
    this->setWindowTitle("Deepin Community Live CD 安装工具 " + QString(APP_VERSION));
    SetDiskList(ui->diskChooser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::GetDiskList(){

}

void MainWindow::SetDiskList(QTableView *diskListWidget){
    QStandardItemModel *nmodel = new QStandardItemModel(this);
    // 设置表头
    DiskControl diskControl;
    QStringList diskPathList;
    QStringList diskFormatList;
    QStringList mountPathList;
    QStringList list2;
    QStringList list3;
    diskControl.GetDiskInfo(&diskPathList, &diskFormatList, &list2, &list3, &mountPathList);
    qDebug() << "=======Disk=========";
    qDebug() << diskPathList;
    qDebug() << diskFormatList;
    int count = diskPathList.size();
    for(int i = 0; i < count; i++){
        nmodel->setItem(i, 0, new QStandardItem(diskPathList.at(i)));
        nmodel->setItem(i, 1, new QStandardItem(diskFormatList.at(i)));
        nmodel->setItem(i, 4, new QStandardItem(mountPathList.at(i)));
    }
    diskListWidget->setModel(nmodel);
    /*QStorageInfo storage = QStorageInfo::root();
    QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
    int count = list.size();
    for(int i = 0; i < count; i++){
        QStorageInfo diskInfo = list.at(i);
        nmodel->setItem(i, 0, new QStandardItem(QString(diskInfo.device())));
        nmodel->setItem(i, 1, new QStandardItem(QString(diskInfo.displayName())));
        nmodel->setItem(i, 2, new QStandardItem(QString(diskInfo.fileSystemType())));
        nmodel->setItem(i, 3, new QStandardItem(QString(diskInfo.name())));
        nmodel->setItem(i, 4, new QStandardItem(QString(diskInfo.subvolume())));
    }*/
    //diskListWidget->setModel(nmodel);
}

// 退出程序
void MainWindow::on_action_exit_triggered()
{
    QApplication *app;
    app->exit();
}

