#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_exit_triggered();

private:
    void SetPart();
    Ui::MainWindow *ui;
    void SetDiskList(QTableView *diskListWidget);
    QStringList GetDiskList();
    QMap<QString, QString> partSet;
};
#endif // MAINWINDOW_H
