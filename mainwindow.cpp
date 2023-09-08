#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStorageInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置程序标题
    this->setWindowTitle("Deepin Community Live CD 安装工具 " + QString(APP_VERSION));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetDiskList(QListWidget *diskListWidget){

}

// 退出程序
void MainWindow::on_action_exit_triggered()
{
    QApplication *app;
    app->exit();
}

