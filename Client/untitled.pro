QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/common.cpp \
    common/user_flse_list.cpp \
    common/form.cpp \
    selfwidget/log_main.cpp \
    selfwidget/log_navigation.cpp \
    selfwidget/login.cpp \
    selfwidget/main.cpp \
    selfwidget/navigation_wg.cpp \
    common/user.cpp \
    common/singletoninfouser.cpp \

HEADERS += \
    common.h \
    form.h \
    log_main.h \
    log_navigation.h \
    login.h \
    navigation_wg.h \
    singletoninfouser.h \
    user.h\
    user_flse_list.h

FORMS += \
    log_main.ui \
    log_navigation.ui \
    login.ui \
    navigation_wg.ui

INCLUDEPATH += include/QsLog.h \
               include/QsLogDest.h \
               include/QsLogDestConsole.h \
               include/QsLogDestFile.h \
               include/QsLogDestFunctor.h \
               include/QsLogDisableForThisFile.h \
               include/QsLogLevel.h

LIBS += $$PWD/QsLog/bin/libQsLog2.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qsr.qrc



