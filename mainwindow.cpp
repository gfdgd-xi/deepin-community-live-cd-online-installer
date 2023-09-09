#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStorageInfo>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include "diskcontrol.h"
#include "editpartdialog.h"

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
    nmodel->setColumnCount(6);
    nmodel->setHeaderData(0, Qt::Horizontal, "分区");
    nmodel->setHeaderData(1, Qt::Horizontal, "分区格式");
    nmodel->setHeaderData(2, Qt::Horizontal, "剩余空间");
    nmodel->setHeaderData(3, Qt::Horizontal, "全部空间");
    nmodel->setHeaderData(4, Qt::Horizontal, "设置挂载点");
    nmodel->setHeaderData(5, Qt::Horizontal, "");
    // 设置不可编辑
    diskListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置选择整行且只能单选
    diskListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    diskListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // 显示信息
    DiskControl diskControl;
    QStringList diskPathList;
    QStringList diskFormatList;
    QStringList mountPathList;
    QStringList freeSpaceList;
    QStringList totalSpaceList;
    diskControl.GetDiskInfo(&diskPathList, &diskFormatList, &freeSpaceList, &totalSpaceList, &mountPathList);
    qDebug() << "=======Disk=========";
    qDebug() << diskPathList;
    qDebug() << diskFormatList;
    qDebug() << mountPathList;
    qDebug() << freeSpaceList;
    qDebug() << totalSpaceList;
    int count = diskPathList.size();
    for(int i = 0; i < count; i++){
        nmodel->setItem(i, 0, new QStandardItem(diskPathList.at(i)));
        nmodel->setItem(i, 1, new QStandardItem(diskFormatList.at(i)));
        nmodel->setItem(i, 2, new QStandardItem(freeSpaceList.at(i)));
        nmodel->setItem(i, 3, new QStandardItem(totalSpaceList.at(i)));
    }
    diskListWidget->setModel(nmodel);
    for(int i = 0; i < count; i++){
        QPushButton *button = new QPushButton("编辑");
        connect(button, &QPushButton::clicked, this, &MainWindow::SetPart);
        diskListWidget->setIndexWidget(nmodel->index(i, 5), button);
    }
}

void MainWindow::SetPart(){
    EditPartDialog *dialog = new EditPartDialog("/dev/sda1", &partSet, this);
    // 堵塞线程
    dialog->setAttribute(Qt::WA_ShowModal, true);
    dialog->show();
    dialog->exec();
}

// 退出程序
void MainWindow::on_action_exit_triggered()
{
    QApplication *app;
    app->exit();
}

