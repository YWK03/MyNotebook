QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    C:/Users/秘密小杨/OneDrive/桌面/img/剪切.png \
    C:/Users/秘密小杨/OneDrive/桌面/img/右撤回.png \
    C:/Users/秘密小杨/OneDrive/桌面/img/左撤回.png \
    C:/Users/秘密小杨/OneDrive/桌面/img/打开.png \
    C:/Users/秘密小杨/OneDrive/桌面/img/文件-复制.png \
    C:/Users/秘密小杨/OneDrive/桌面/img/文件保存.png \
    C:/Users/秘密小杨/OneDrive/桌面/img/新建.png
