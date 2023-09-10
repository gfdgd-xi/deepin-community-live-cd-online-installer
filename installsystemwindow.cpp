#include "installsystemwindow.h"
#include "ui_installsystemwindow.h"
#include <qtermwidget5/qtermwidget.h>

InstallSystemWindow::InstallSystemWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstallSystemWindow)
{
    ui->setupUi(this);
    QTermWidget *ter = new QTermWidget();
    ui->verticalLayout->addWidget(ter);
}

InstallSystemWindow::~InstallSystemWindow()
{
    delete ui;
}
