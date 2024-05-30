QT       += core gui

QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    authregform.cpp \
    functionsforclient.cpp \
    main.cpp \
    mainwindow.cpp \
    singletonclient.cpp \
    task_one.cpp \
    vigenerecipher.cpp

HEADERS += \
    admin.h \
    authregform.h \
    functionsforclient.h \
    mainwindow.h \
    singletonclient.h \
    task_one.h \
    user_data.h \
    vigenerecipher.h

FORMS += \
    admin.ui \
    authregform.ui \
    mainwindow.ui \
    task_one.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
