########
MOCK_LIB=../../../../mocks_library
########

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$MOCK_LIB

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    utility/painter.cpp

HEADERS += \
    character.h \
    characters.h \
    context.h \
    controller.h \
    field.h \
    field_elements.h \
    game.h \
    mainwindow.h \
    object.h \
    objects.h \
    player.h \
    utility/assets.h \
    utility/painter.h \
    utility/geometry.h \
    utility/random.h \
    utility/timer.h \
    utility/utility.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    game.qrc
