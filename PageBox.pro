QT += widgets

TEMPLATE = lib
DEFINES += PAGEBOX_LIBRARY

CONFIG += c++11

include(../config.pri)

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
    pageanimcanvas.cpp \
    pagebox.cpp \
    pageboxdocitem.cpp \
    pageboxpageitem.cpp \
    pageboxplugin.cpp \
    pageboxtoolbar.cpp \
    pagemodelcontrolwidget.cpp \
    pagenumberwidget.cpp \
    pagesource.cpp \
    qpropertybinding.cpp \
    qpropertybindings.cpp

HEADERS += \
    PageBox_global.h \
    pageanimcanvas.h \
    pagebox.h \
    pageboxdocitem.h \
    pageboxpageitem.h \
    pageboxplugin.h \
    pageboxtoolbar.h \
    pagemodelcontrolwidget.h \
    pagenumberwidget.h \
    pagesource.h \
    qpropertybinding.h \
    qpropertybindings.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtEventBus/release/ -lQtEventBus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtEventBus/debug/ -lQtEventBusd
else:unix: LIBS += -L$$OUT_PWD/../QtEventBus/ -lQtEventBus

INCLUDEPATH += $$PWD/../QtEventBus
DEPENDPATH += $$PWD/../QtEventBus

INCLUDEPATH += $$PWD/../QtPromise/src

INCLUDEPATH += $$PWD/../qtpromise/src/qtpromise $$PWD/../qtpromise/include
#DEPENDPATH += $$PWD/../qtpromise/src/qtpromise

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ShowBoard/release/ -lShowBoard
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ShowBoard/debug/ -lShowBoardd
else:unix: LIBS += -L$$OUT_PWD/../ShowBoard/ -lShowBoard

INCLUDEPATH += $$PWD/../ShowBoard
DEPENDPATH += $$PWD/../ShowBoard

