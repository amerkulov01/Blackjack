QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/DeckSetup.cpp \
    src/cards.cpp \
    src/dealer.cpp \
    src/gameui.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/player.cpp \
    src/startmenu.cpp \
    src/wallet.cpp

HEADERS += \
    headers/DeckSetup.h \
    headers/cards.h \
    headers/dealer.h \
    headers/gameui.h \
    headers/mainwindow.h \
    headers/player.h \
    headers/startmenu.h \
    headers/wallet.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/images.qrc

DISTFILES += \
    README.md
