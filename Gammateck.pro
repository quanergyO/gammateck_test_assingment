QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/datareceiver.cpp \
    src/figuretablemodel.cpp \
    src/infowidget.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/renderwidget.cpp \
    src/typesdao.cpp

HEADERS += \
    include/datareceiver.h \
    include/figuretablemodel.h \
    include/infowidget.h \
    include/mainwindow.h \
    include/renderwidget.h \
    include/api_generated.h \
    include/typesdao.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
