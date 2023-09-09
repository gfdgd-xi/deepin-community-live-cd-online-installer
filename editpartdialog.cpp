#include "editpartdialog.h"
#include "ui_editpartdialog.h"

EditPartDialog::EditPartDialog(QString part, QMap<QString, QString> *partSet, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPartDialog)
{
    ui->setupUi(this);
}

EditPartDialog::~EditPartDialog()
{
    delete ui;
}
