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
    // 格式化分区
    QStringList list = partSetPartFormat.keys();
    for (int i = 0; i < list.size(); i++) {
        this->command->AddCommand("umount '" + list[i] + "'");
        this->command->AddCommand("mkfs." + partSetPartFormat[list[i]] + " -V '" + list[i] + "'");
    }
    // 挂载分区
    this->command->AddCommand("umount /tmp/dclc-installer");
    this->command->AddCommand("mkdir -p -v /tmp/dclc-installer");
    QString rootPath = "";
    list = partSetMountPoint.keys();
    for (int i = 0; i < list.size(); i++) {
        if(partSetMountPoint[list[i]] == "/"){
            this->command->AddCommand("mount '" + list[i] + "' /tmp/dclc-installer");
            rootPath = list[i];
            break;
        }
    }
    // 获取 Debian Base System
    this->command->AddCommand("debootstrap bookworm /tmp/dclc-installer https://mirrors.sjtug.sjtu.edu.cn/debian");
    // 挂载挂载点
    this->command->AddCommand("mount --bind /dev /tmp/dclc-installer/dev");
    this->command->AddCommand("mount --bind /run /tmp/dclc-installer/run");
    this->command->AddCommand("mount -t devpts devpts /tmp/dclc-installer/dev/pts");
    this->command->AddCommand("mount -t sysfs sysfs /tmp/dclc-installer/sys");
    this->command->AddCommand("mount -t proc proc /tmp/dclc-installer/proc");
    this->command->AddCommand("mount -t tmpfs tmpfs /tmp/dclc-installer/tmpfs");
    // 获取 /boot 挂载点并挂载
    this->command->AddCommand("mkdir -p /tmp/dclc-installer/boot");
    QString bootPath = "";
    for (int i = 0; i < list.size(); i++) {
        if(partSetMountPoint[list[i]] == "/boot"){
            this->command->AddCommand("mount '" + list[i] + "' /tmp/dclc-installer/boot");
            bootPath = list[i];
            break;
        }
    }
    // 获取 /boot/efi 挂载点并挂载
    QString bootEFIPath = "";
    this->command->AddCommand("mkdir -p /tmp/dclc-installer/boot/efi");
    for (int i = 0; i < list.size(); i++) {
        if(partSetMountPoint[list[i]] == "/boot/efi"){
            this->command->AddCommand("mount '" + list[i] + "' /tmp/dclc-installer/boot/efi");
            bootEFIPath = list[i];
            break;
        }
    }
    // 刷新软件列表
    this->command->AddCommand("chroot /tmp/dclc-installer apt update");
    // 安装内核
    this->command->AddCommand("chroot /tmp/dclc-installer apt install linux-headers-amd64 linux-image-amd64 -y");
    // 安装 xfce4 桌面
    this->command->AddCommand("chroot /tmp/dclc-installer apt install xfce4 lightdm -y");
    // Flag: root密码设置以及创建用户密码
    // 设置 /sbin 下的命令可以被直接运行而无需用 /sbin/xxx 的形式
    // 支持安装桌面环境（Debian 为 xfce4，deepin 为 dde）
    // 支持设置为中文
    // 设置引导
    this->command->AddCommand("chroot /tmp/dclc-installer apt install grub-pc grub-common -y");
    this->command->AddCommand("chroot /tmp/dclc-installer grub-mkconfig -o /boot/grub/grub.cfg");
    // 如果是传统启动
    QString rootPathDisk = rootPath;
    for(int i = 0; i < 10; i++){
        rootPathDisk = rootPathDisk.replace(QString::number(i), "");
    }

    this->command->AddCommand("chroot /tmp/dclc-installer grub-install '" + rootPathDisk + "'"); // 有问题
    // UEFI 启动
    // this->command->AddCommand("grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=GRUB");
    this->command->AddCommand("chroot /tmp/dclc-installer update-grub2");
    // 取消挂载分区
    this->command->AddCommand("umount /tmp/dclc-installer/tmpfs");
    this->command->AddCommand("umount /tmp/dclc-installer/run");
    this->command->AddCommand("umount /tmp/dclc-installer/dev/pts");
    this->command->AddCommand("umount /tmp/dclc-installer/dev");
    this->command->AddCommand("umount /tmp/dclc-installer/sys");
    this->command->AddCommand("umount /tmp/dclc-installer/proc");
    if(bootEFIPath != ""){
        this->command->AddCommand("umount /tmp/dclc-installer/boot/efi");
    }
    if(bootPath != ""){
        this->command->AddCommand("umount /tmp/dclc-installer/boot/");
    }
    this->command->AddCommand("umount /tmp/dclc-installer");
    this->command->AddCommand("read");
    this->command->RunCommand();
}
