#include "installsystem.h"
#include "runcommandinterminal.h"
#include <QFile>
#include <qtermwidget5/qtermwidget.h>
#include <QProgressBar>

InstallSystem::InstallSystem(QTermWidget *terminal, QProgressBar *progressbar, QMap<QString, QString> partSetPartFormat, QMap<QString, QString> partSetMountPoint)
{
    this->terminal = terminal;
    this->progressbar = progressbar;
    this->partSetMountPoint = partSetMountPoint;
    this->partSetPartFormat = partSetPartFormat;
    this->command = new RunCommandInTerminal(this->terminal, this->progressbar);
    //this->command->AddCommand("zenity --info");
    QStringList list = partSetPartFormat.keys();
    for (int i = 0; i < list.size(); i++) {
        this->command->AddCommand("umount '" + list[i] + "'");
        this->command->AddCommand("mkfs." + partSetPartFormat[list[i]] + " -V '" + list[i] + "'");
    }
    //this->command->AddCommand("");
    this->command->AddCommand("umount /tmp/dclc-installer");
    this->command->AddCommand("mkdir -p -v /tmp/dclc-installer");
    //this->command->AddCommand("mount '" + partSetMountPoint["/"] + "' /tmp/dclc-installer");
    list = partSetMountPoint.keys();
    for (int i = 0; i < list.size(); i++) {
        if(partSetMountPoint[list[i]] == "/"){
            this->command->AddCommand("mount '" + list[i] + "' /tmp/dclc-installer");
            break;
        }
        //
    }
    this->command->AddCommand("debootstrap bookworm /tmp/dclc-installer");
    this->command->AddCommand("read");
    this->command->RunCommand();
}
