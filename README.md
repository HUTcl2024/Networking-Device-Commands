# Networking Device Commands（USB 设备扫描工具）

## 项目简介

本项目使用 **C 语言** 编写，实现了在 **Windows 操作系统** 下列出当前系统中所有 USB 设备的信息。

程序通过调用 **Windows SetupAPI** 获取系统设备列表，并筛选出 USB 设备，然后显示每个设备的名称（Name）和硬件 ID（Hardware ID）。

该项目主要用于学习 **Windows 设备管理接口（SetupAPI）** 以及 **USB 设备枚举机制**。

---

## 功能特点

本程序实现了以下功能：

* 列出当前系统中的 USB 设备
* 显示 USB 设备名称（Device Name）
* 显示 USB 硬件 ID（Hardware ID）
* 统计系统中检测到的 USB 设备数量

---
## 运行环境

程序需要以下运行环境：

* 操作系统：Windows
* 编译器：GCC（MinGW / MinGW-w64）
* 开发接口：Windows SetupAPI
* 电脑需要具备 USB 控制器

---

## 编译方法

在项目目录中打开 **PowerShell 或 CMD**，执行：

```bash
gcc usb_list.c -o usb_list -lsetupapi
```

---

## 运行程序

编译完成后运行：

```bash
.\usb_list.exe
```

程序将自动扫描系统中的 USB 设备并输出设备信息。

---

## 项目结构

```
Networking-Device-Commands
│
├── usb_list.c       # USB设备扫描程序源码
├── usb_list.exe     # 编译后的可执行文件
└── README.md        # 项目说明文档
```

---

## 技术说明

本程序使用 Windows SetupAPI 来访问系统设备信息，核心 API 包括：

* `SetupDiGetClassDevs()`
* `SetupDiEnumDeviceInfo()`
* `SetupDiGetDeviceRegistryProperty()`
* `WideCharToMultiByte()`

这些 API 用于枚举系统设备并读取设备属性信息。

---

## 作者

GitHub 用户：**HUTcl2024**


