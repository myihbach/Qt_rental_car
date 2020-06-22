QT       += core gui sql widgets

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
    client.cpp \
    formclient.cpp \
    formmaintenance.cpp \
    formreservation.cpp \
    formupdatereservation.cpp \
    formupdatevoiture.cpp \
    formvoiture.cpp \
    location.cpp \
    main.cpp \
    maintenance.cpp \
    myk_car.cpp \
    resultat.cpp \
    voiture.cpp

HEADERS += \
    client.h \
    formclient.h \
    formmaintenance.h \
    formreservation.h \
    formupdatereservation.h \
    formupdatevoiture.h \
    formvoiture.h \
    location.h \
    maintenance.h \
    myk_car.h \
    resultat.h \
    voiture.h

FORMS += \
    client.ui \
    formclient.ui \
    formmaintenance.ui \
    formreservation.ui \
    formupdatereservation.ui \
    formupdatevoiture.ui \
    formvoiture.ui \
    location.ui \
    maintenance.ui \
    myk_car.ui \
    resultat.ui \
    voiture.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    myk_resources.qrc
