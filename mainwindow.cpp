#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStorageInfo>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include "diskcontrol.h"
#include "editpartdialog.h"
#include "aboutprogram.h"

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
    nmodel->setHeaderData(5, Qt::Horizontal, "是否格式化");
    //nmodel->setHeaderData(6, Qt::Horizontal, "");
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
        QString diskPath = diskPathList.at(i);
        nmodel->setItem(i, 0, new QStandardItem(diskPath));
        nmodel->setItem(i, 1, new QStandardItem(diskFormatList.at(i)));
        nmodel->setItem(i, 2, new QStandardItem(freeSpaceList.at(i)));
        nmodel->setItem(i, 3, new QStandardItem(totalSpaceList.at(i)));
        if(partSetMountPoint.count(diskPath)){
            nmodel->setItem(i, 4, new QStandardItem(partSetMountPoint.value(diskPath)));
        }
        if(partSetPartFormat.count(diskPath)){
            nmodel->setItem(i, 5, new QStandardItem(partSetPartFormat.value(diskPath)));
        }
    }
    diskListWidget->setModel(nmodel);
}

// 退出程序
void MainWindow::on_action_exit_triggered()
{
    QApplication *app;
    app->exit();
}


void MainWindow::on_refreshDiskList_clicked()
{
    SetDiskList(ui->diskChooser);
}


void MainWindow::on_editChoosePart_clicked()
{
    // 获取选择内容
    int index = ui->diskChooser->currentIndex().row();
    if(index == -1){
        QMessageBox::information(this, "提示", "请先选择分区才能编辑");
        return;
    }
    QAbstractItemModel *model = ui->diskChooser->model();
    QString part = model->index(index, 0).data().toString();
    // 创建对话框
    EditPartDialog *dialog = new EditPartDialog(part, &partSetMountPoint, &partSetPartFormat, this);
    // 堵塞线程
    dialog->setAttribute(Qt::WA_ShowModal, true);
    dialog->show();
    if(dialog->exec()){
        // 只有在按确定时才刷新列表
        SetDiskList(ui->diskChooser);
        QString showMsg = "当前状态：设置" + part;
        if(partSetMountPoint.count(part)){
            showMsg += "挂载点为" + partSetMountPoint.value(part);
        }
        if(partSetPartFormat.count(part)){
            showMsg += "并格式化为" + partSetPartFormat.value(part) + "格式";
        }
        ui->statusbar->showMessage(showMsg);
    }
    delete dialog;
}


void MainWindow::on_userName_textChanged(const QString &arg1)
{
    // 自动清除空格
    ui->userName->setText(ui->userName->text().replace(" ", ""));
}


void MainWindow::on_hostName_textChanged(const QString &arg1)
{
    // 自动清除空格
    ui->hostName->setText(ui->hostName->text().replace(" ", ""));
}


void MainWindow::on_rootPassword0_textChanged(const QString &arg1)
{
    // 如果密码不相同就显示提示
    if(ui->rootPassword0->text() == ui->rootPassword1->text()){
        ui->rootPasswordTips0->setText("root 用户密码：<a style='color: green;'><b>√</b></a>");
        ui->rootPasswordTips1->setText("再输一次root用户密码：<a style='color: green;'><b>√</b></a>");
    }
    else{
        ui->rootPasswordTips1->setText("再输一次root用户密码：<a style='color: red;'><b>×</b></a>两次密码不相同！");
    }
    // 空密码提示
    if(ui->rootPassword0->text() == ""){
        ui->rootPasswordTips0->setText("root 用户密码：<a style='color: red;'><b>×</b></a>密码不能为空");
    }
    else{
        ui->rootPasswordTips0->setText("root 用户密码：<a style='color: green;'><b>√</b></a>");
    }
    if(ui->rootPassword1->text() == ""){
        ui->rootPasswordTips1->setText("再输一次root用户密码：<a style='color: red;'><b>×</b></a>密码不能为空");
    }
}


void MainWindow::on_rootPassword1_textChanged(const QString &arg1)
{
    // 如果密码不相同就显示提示
    if(ui->rootPassword0->text() == ui->rootPassword1->text()){
        ui->rootPasswordTips0->setText("root 用户密码：<a style='color: green;'><b>√</b></a>");
        ui->rootPasswordTips1->setText("再输一次root用户密码：<a style='color: green;'><b>√</b></a>");
    }
    else{
        ui->rootPasswordTips1->setText("再输一次root用户密码：<a style='color: red;'><b>×</b></a>两次密码不相同！");
    }
    // 空密码提示
    if(ui->rootPassword0->text() == ""){
        ui->rootPasswordTips0->setText("root 用户密码：<a style='color: red;'><b>×</b></a>密码不能为空");
    }
    else{
        ui->rootPasswordTips0->setText("root 用户密码：<a style='color: green;'><b>√</b></a>");
    }
    if(ui->rootPassword1->text() == ""){
        ui->rootPasswordTips1->setText("再输一次root用户密码：<a style='color: red;'><b>×</b></a>密码不能为空");
    }
}


void MainWindow::on_action_about_triggered()
{
    // 显示关于窗口
    AboutProgram program;
    // 堵塞线程
    program.setAttribute(Qt::WA_ShowModal, true);
    program.show();
    program.exec();
}

