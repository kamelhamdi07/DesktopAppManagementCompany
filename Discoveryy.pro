QT       += core gui sql serialport
QT += printsupport
QT += core gui network
QT += core gui sql axcontainer printsupport
QT       += core gui multimedia multimediawidgets
QT       += sql
QT       += sql
QT += printsupport
QT       +=charts


QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    arduino.cpp \
    arduino1.cpp \
    chat.cpp \
    conf.cpp \
    conference.cpp \
    connection.cpp \
    dialog.cpp \
    incendie.cpp \
    login.cpp \
    main.cpp \
    home.cpp \
    mat.cpp \
    materille.cpp \
    perso.cpp \
    personnel.cpp \
    publication.cpp \
    reff.cpp \
    smtp.cpp

HEADERS += \
    admin.h \
    arduino.h \
    arduino1.h \
    chat.h \
    conf.h \
    conference.h \
    connection.h \
    dialog.h \
    home.h \
    incendie.h \
    login.h \
    mat.h \
    materille.h \
    perso.h \
    personnel.h \
    publication.h \
    reff.h \
    smtp.h

FORMS += \
    chat.ui \
    conf.ui \
    dialog.ui \
    home.ui \
    incendie.ui \
    login.ui \
    materille.ui \
    perso.ui \
    reff.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icon/334962190_713957570385466_8174413079122733394_n.png \
    Icon/337326932_883576556203240_9054454841976748620_n.png \
    Icon/340459101_570072101880922_8450964117292741454_n.png \
    Icon/340746670_937324410936244_4625091873557112592_n.png \
    Icon/article-16.png \
    Icon/article-24.png \
    Icon/book (1).svg \
    Icon/book.svg \
    Icon/check-mark-3-32.ico \
    Icon/closeAsset 43.png \
    Icon/conference-32.png \
    Icon/decision-32.png \
    Icon/hideAsset 53.png \
    Icon/homeAsset 46.png \
    Icon/icons/1x/androidAsset 49.png \
    Icon/icons/1x/arrow.png \
    Icon/icons/1x/bookAsset 57.png \
    Icon/icons/1x/bugAsset 47.png \
    Icon/icons/1x/bulletAsset 54.png \
    Icon/icons/1x/cleanAsset 59.png \
    Icon/icons/1x/closeAsset 43.png \
    Icon/icons/1x/cloudAsset 48.png \
    Icon/icons/1x/dragAsset 52.png \
    Icon/icons/1x/errorAsset 55.png \
    Icon/icons/1x/gameAsset 61.png \
    Icon/icons/1x/hideAsset 53 - Copy.png \
    Icon/icons/1x/hideAsset 53.png \
    Icon/icons/1x/homeAsset 46.png \
    Icon/icons/1x/logo.png \
    Icon/icons/1x/max - Copy.png \
    Icon/icons/1x/max.png \
    Icon/icons/1x/peopleAsset 62.png \
    Icon/icons/1x/peple.png \
    Icon/icons/1x/restore.png \
    Icon/icons/1x/settAsset 50.png \
    Icon/icons/1x/smile2Asset 1.png \
    Icon/icons/1x/smileAsset 1.png \
    Icon/icons/1x/windAsset 51.png \
    Icon/icons/1x/worldAsset 60.png \
    Icon/icons8-add-new-60.png \
    Icon/icons8-business-50.png \
    Icon/icons8-chat-bot-64.png \
    Icon/icons8-data-backup-48.png \
    Icon/icons8-home-page-90.png \
    Icon/icons8-identity-theft-50.png \
    Icon/icons8-money-yours-90.png \
    Icon/icons8-pen-squared-32.png \
    Icon/icons8-pen-squared-48.png \
    Icon/icons8-pen-squared-64.png \
    Icon/icons8-pen-squared-96.png \
    Icon/icons8-print-30.png \
    Icon/icons8-reset-50.png \
    Icon/icons8-update-left-rotation-50.png \
    Icon/log-removebg-preview.png \
    Icon/log-removebg-preview1.png \
    Icon/map-32.ico \
    Icon/max - Copy.png \
    Icon/peple.png \
    Icon/printer-3-32 - Copie.ico \
    Icon/product-24.png \
    Icon/search-14-32.png \
    Icon/settings-24-24.ico \
    Icon/trash-2-32.ico \
    Icon/user.svg \
    Icon/x-mark-32.ico
