QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../Adfgvx
INCLUDEPATH += ../Viginere
INCLUDEPATH += ../Playfair

SOURCES += \
    ../Adfgvx/adfgvx.cpp \
    ../Adfgvx/adfgvxWidget.cpp \
    ../Playfair/playfair.cpp \
    ../Playfair/playfairWidget.cpp \
    ../Viginere/vigenere.cpp \
    ../Viginere/vigenereWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../Adfgvx/adfgvx.h \
    ../Adfgvx/adfgvxWidget.h \
    ../Playfair/playfair.h \
    ../Playfair/playfairWidget.h \
    ../Viginere/vigenere.h \
    ../Viginere/vigenereWidget.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
