# Noita Archive Manager 存档管理器

- ## [程序说明及介绍视频](https://www.bilibili.com/video/BV1PH4y1g7u2/?vd_source=b94494fff1b1147eb0072109b3ee55bc)

- [gitHub主页](https://github.com/Xiaomony/NoitaArchiveManager.git)

- [使用说明及注意事项](#使用说明及注意事项)

- [实现原理](#实现原理)

- [构建环境](#构建环境)

- [问题反馈](#问题反馈)
  
## 使用说明及注意事项

1. 本程序运行时会在程序所在目录下建立一个 **_Archive文件夹_** 用于存储日志文件和保存的存档,请勿删除(若删除,则相当于恢复程序第一次运行的状态)

2. 建议将程序放在磁盘中的某个文件夹下,再发送到桌面快捷方式使用(避免程序在桌面创建Archive文件夹后被误删)

3. 请在Noita主界面有 **"继续"** 这一选项时读取存档,若没有则请先 **"新游戏"** 后再关闭游戏读档,重新打开后再点击 **"继续"**

4. 建议关闭Steam云存档

5. 请在Noita **_正常保存、关闭_** 后再进行存档(游戏进行中存档的话保存的是Noita的 **自动存档** ,可能是几分钟前的存档,并非保存时的存档)

6. 游戏进行中请勿读取存档

7. 随着游戏的进行,每次存档 **所用的时间** 和 **占用的空间** 也会不断 **增大** ,请耐心等待

8. 命令操作：
   | 命令          | 含义             | 简写  | 说明                           |
   |:-----------:|:--------------:|:---:|:----------------------------:|
   | quit        |                | q   | 退出程序                         |
   | help        |                | h   | 帮助及注意事项                      |
   | clearScreen |                | cls | 清屏                           |
   | save        |                | s   | 保存（存档）                       |
   | qsave       | quick save     | qs  | 快速保存（无需填写存档名称和备注）            |
   | rsave       | repalce save   | rs  | 保存 且 覆盖最新存档（存档名与备注不变，存档时间更新） |
   | load        |                | l   | 指定存档进行读取                     |
   | qload       | quick load     | ql  | 快速读取（最近一次的存档）                |
   | log         |                | lo  | 查看所有存档极其信息                   |
   | slog        | short log      | sl  | 查看近七次存档                |
   | mArchive    | modify Archive | ma  | 修改某个存档的信息                    |
   | delArch     | delete Archive | del | 删除某个存档                       |
   | qDelete     | quick Delete   | qd  | 删除最新的存档                      |
   | usage       |                | use | 查看存档的占用空间            |

## 实现原理

Noita会在`C:\Users\用户名\AppData\LocalLow\Nolla_Games_Noita`下存储数据，其中的`save00`文件夹为存档数据，通过复制该文件夹的内容并还原以达到存档和读档的目的

## 构建环境

- CMake VERSION 3.15
- MinGW gcc version 13.2.0

**_构建时注意要将cmake与mingw32-make添加到环境变量_**

>若未将cmake或mingw添加到环境变量,则分别需要将build.bat中的MAKER改为cmake的路径,GENERATOR改为mingw下bin目录的路径

```bat
set MAKER= path_to_cmake/cmake.exe
set GENERATOR= path_to_mingw/bin/mingw32-make.exe
```

#### 构建：直接运行build.bat

## 问题反馈

如在使用中存在问题，可以通过gitHub或[Bilibili发私信](https://space.bilibili.com/506901263)
