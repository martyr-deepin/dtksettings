# Dtk Settings

Dtk Settings is a module of Dtk, which can generate user config and UI dialog from json.

![screenshot](https://raw.githubusercontent.com/linuxdeepin/dtksettings/master/docs/dtk-settings-dialog.png)

# Dependencies

Support platform:

- Deepin 2015

- Mac OS 10.12+

- Windows 7 32/64bit, Windows 8 32/64 bit.

# Installation

## Repository Install

If you are deepin user, you can install from repository:

```bash
sudo apt-get install libdtksettingsview libdtksettings
```

## Build and install

### Linux Platform

#### Install Build Dependencies

Release base debian

```bash
sudo apt-get install debhelper qt5-default qt5-qmake qttools5-dev-tools
```

#### Build

```
mkdir build
cd build
qmake -r ..
make install
```

### Windows Platform

#### Development Environment

- Windows 10
- Microsoft Visual C++ 2017
- Qt5.8

#### Build and Install

```
mkdir build
cd build
qmake "LIB_INSTALL_DIR=D:/Develop/lib" "INCLUDE_INSTALL_DIR=D:/Develop/include" -r ..
nmake
nmake install
```

### Mac OS Platform

#### Development Environment

- Mac OS 10.12+
- Qt5.8

#### Set Qt PATH

```
export QtInstallPath=/User/yourhome/Qt5.8/5.8/clang_64
export PATH=$QtInstallPath/bin:$PATH
```

### Build and Install

```
mkdir build
cd build
qmake "LIB_INSTALL_DIR=/usr/local/lib" "INCLUDE_INSTALL_DIR=/usr/local/include" -r ..
make
make install
```

# Getting help

Any usage issues can ask for help via

* [Gitter](https://gitter.im/orgs/linuxdeepin/rooms)
* [IRC channel](https://webchat.freenode.net/?channels=deepin)
* [Forum](https://bbs.deepin.org)
* [WiKi](https://wiki.deepin.org/)

# Getting involved

We encourage you to report issues and contribute changes

* [Contribution guide for users.](http://wiki.deepin.org/index.php?title=Contribution_Guidelines_for_Users)
* [Contribution guide for developers.](http://wiki.deepin.org/index.php?title=Contribution_Guidelines_for_Developers).

# License

Dtk Settings is licensed under [GPLv3](LICENSE).
