QT += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/controller.cpp \
    src/core.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/parsermath.cpp \
    src/qcustomplot.cpp

HEADERS += \
    include/controller.h \
    include/core.h \
    include/mainwindow.h \
    include/parsermath.h \
    include/qcustomplot.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
win32-g++:QMAKE_CXXFLAGS += -Wa,-mbig-obj
win32-g++:QMAKE_CFLAGS   += -Wa,-mbig-obj
