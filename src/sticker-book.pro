QT += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    models/copyprofile.cpp \
    models/copyprofilelistmodel.cpp \
    windows/aboutwindow.cpp \
    windows/addcopyprofilewindow.cpp \
    windows/mainwindow.cpp \
    windows/optionswindow.cpp

HEADERS += \
    constants.h \
    models/copyprofile.h \
    models/copyprofilelistmodel.h \
    windows/aboutwindow.h \
    windows/addcopyprofilewindow.h \
    windows/mainwindow.h \
    windows/optionswindow.h

FORMS += \
    windows/aboutwindow.ui \
    windows/addcopyprofilewindow.ui \
    windows/mainwindow.ui \
    windows/optionswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
