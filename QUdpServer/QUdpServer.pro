QT -= gui
QT += core network

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = QUdpSocket

TEMPLATE = app

QMAKE_CXXFLAGS += -DHANDLER_TYPE=duplications

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        udpserver.cpp \
        ../handlers/handler_factory.cpp \
        ../handlers/duplications_handler.cpp \
        ../handlers/palindromes_handler.cpp

HEADERS += \
        udpserver.h \
        ../handlers/handler_factory.h \
        ../handlers/handler_interface.h \
        ../handlers/duplications_handler.h \
        ../handlers/palindromes_handler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    udpserver.h
