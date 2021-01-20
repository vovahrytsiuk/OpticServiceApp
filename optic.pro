QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += release


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addappform.cpp \
    addappoinmentinfoform.cpp \
    adddoctorform.cpp \
    addsalonform.cpp \
    appeditform.cpp \
    clienteditform.cpp \
    customform.cpp \
    doctoreditform.cpp \
    insertclient.cpp \
    main.cpp \
    mainwindow.cpp \
    saloneditform.cpp

HEADERS += \
    addappform.h \
    addappoinmentinfoform.h \
    adddoctorform.h \
    addsalonform.h \
    appeditform.h \
    clienteditform.h \
    customform.h \
    doctoreditform.h \
    insertclient.h \
    mainwindow.h \
    saloneditform.h

FORMS += \
    addappform.ui \
    addappoinmentinfoform.ui \
    adddoctorform.ui \
    addsalonform.ui \
    appeditform.ui \
    clienteditform.ui \
    customform.ui \
    doctoreditform.ui \
    insertclient.ui \
    mainwindow.ui \
    saloneditform.ui

INCLUDEPATH+=/usr/include
LIBS+=-L/usr/lib -lpq

#INCLUDEPATH += "/Library/PostgreSQL/12/include"
#LIBS+="/Library/PostgreSQL/12/lib/libpq.dylib"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
