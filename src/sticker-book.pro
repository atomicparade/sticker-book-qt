QT += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += \
    translations/lang_en.ts \
    translations/lang_es.ts

RESOURCES += \
    translations/lang_en.qm \
    translations/lang_es.qm

win32 {
    RC_ICONS = assets/icon.ico
}

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = Atomic Parade
QMAKE_TARGET_PRODUCT = "Sticker Book"
QMAKE_TARGET_COPYRIGHT = "Copyright Atomic Parade 2020"

DEFINES += \
    ORGANIZATION_NAME="\"\\\"$$QMAKE_TARGET_COMPANY\\\"\"" \
    PRODUCT_NAME="\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\"" \
    VERSION_STRING="\"\\\"$$VERSION\\\"\"" \
    COPYRIGHT_STRING="\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\""

SOURCES += \
    main.cpp \
    models/copyprofile.cpp \
    models/copyprofilelistmodel.cpp \
    models/sticker.cpp \
    views/stickergrid.cpp \
    windows/aboutwindow.cpp \
    windows/addcopyprofilewindow.cpp \
    windows/mainwindow.cpp \
    windows/optionswindow.cpp

HEADERS += \
    models/copyprofile.h \
    models/copyprofilelistmodel.h \
    models/sticker.h \
    views/stickergrid.h \
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
