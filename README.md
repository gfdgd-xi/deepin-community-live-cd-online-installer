<p width=100px align="center"><img src="icon.svg"></p>
<h1 align="center">Deepin Community Live CD 在线系统安装工具（未完成）</h1>
<hr>
<a href='https://gitee.com/gfdgd-xi/deepin-community-live-cd-online-installer/stargazers'><img src='https://gitee.com/gfdgd-xi/deepin-community-live-cd-online-installer/badge/star.svg?theme=dark' alt='star'></img></a>
<a href='https://gitee.com/gfdgd-xi/deepin-community-live-cd-online-installer/members'><img src='https://gitee.com/gfdgd-xi/deepin-community-live-cd-online-installer/badge/fork.svg?theme=dark' alt='fork'></img></a>  


Deepin Community Live CD 在线安装工具是一个能在 Live CD 上自动从互联网获取系统安装包安装系统的工具  
目前支持安装 Debian  
该程序依照 GPLV3 开源  
Deepin Community Live CD 地址：https://gitee.com/gfdgd-xi/deepin-community-live-cd  

## 编译方法
```bash
sudo apt install qt5-default git make libqtermwidget5-0-dev
git clone https://gitee.com/gfdgd-xi/deepin-community-live-cd-online-installer
cd deepin-community-live-cd-online-installer
qmake .
make -j4
```

## ©2022~Now gfdgd xi