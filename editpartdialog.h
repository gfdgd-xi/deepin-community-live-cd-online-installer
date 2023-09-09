#ifndef EDITPARTDIALOG_H
#define EDITPARTDIALOG_H

#include <QDialog>

namespace Ui {
class EditPartDialog;
}

class EditPartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPartDialog(QString part, QMap<QString, QString> *partSet, QWidget *parent = nullptr);
    ~EditPartDialog();

private:
    Ui::EditPartDialog *ui;
};

#endif // EDITPARTDIALOG_H
