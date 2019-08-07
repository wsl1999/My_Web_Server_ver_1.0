# WEB SERVER Ver 1.0

#### 基于Linux的C++课程大作业

## 服务器设计者

- 王帅龙	清华大学物理系	基科72班

## 服务器开发环境

- Linux系统：Ubuntu 16.04

- 虚拟机：VMware Workstation 12 Pro

- GNU/GCC  Compiler：Code::Blocks 13.12

## 运行服务器

- 打开Web服务器程序所在文件夹，右键 `open terminal` 运行Terminal终端。
- 终端中输入 `./server -h` 查看命令行参数说明，或者输入 `./server` 直接使用默认参数。
- 根据命令行反馈的 `Bind success!` 提示，在右侧的IP地址上右键点击 `open link` ，Ubuntu就会帮你在默认的Firefox浏览器中打开服务器主页。也可以先打开浏览器，然后在地址栏输入Bind后的IP地址。
- 点击主页上的链接，就可以在网页上 `GET` Web服务器的各项信息了。
- 在信息生成页面下端点击 `HERE` ，可返回服务器主页。

## Makefile文件说明

- `Makefile` 文件里定义了服务器程序中各文件的依赖关系，用于 `terminal` 中编译源代码，可辅助理解Web服务器的程序架构（**尤其是参数传递机制**）。

- 若要刷新可执行文件 `server` ，需要在命令行中执行 `make clean` 命令，清除现有的 `.o`， `.so` 文件。

  然后重新执行 `make` 命令即可。

## 服务器实现功能说明

- 使用网络套接字 `socket` 创建Web服务器，动态生成Web网页。
- 实现 `HTTP 1.0 GET` 请求。
- 动态装载服务模块，获取系统信息。
- 使用进程池调配运行内存，在子进程中处理客户请求，提高程序运行效率和稳定性。

## 模块功能说明（动态库装载实现）

- 显示当前系统时间：`time.so`
- 显示Linux发布版本：`issue.so`
- 显示CPU信息：`cpuinfo.so`
- 显示当前进程信息：`process.so`
- 显示磁盘占用信息：`disk.so`

## 启用或禁用模块

#### 启用

- 各服务模块文件名存放在 `modulelist` 文件中，默认装载全部模块。

#### 禁用

- 打开 `modulelist` 文件，在文件名前面添加 `#` 号来禁用相应服务模块，加了 `#` 号的服务模块不会被装载。

  

## 联系方式

#### 电话

- ​	18801022739

#### 邮箱

- ​	wangshuailong1999@163.com
  ​	wsl17@mails.tsinghua.edu.cn
  
  

<u>Copyright © 2019</u>

<u>Wang Shuailong, Department of Physics, Tsinghua University.</u> 

<u>All Rights reserved.</u>