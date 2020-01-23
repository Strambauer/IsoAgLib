TEMPLATE = app
CONFIG -= qt

TARGET = ${INSERT_QMAKE_PROJECT}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /opt/qt5pi/sysroot/usr/include

LIBS += -L/opt/qt5pi/sysroot/usr/lib -lwiringPi

INCLUDEPATH += ${INSERT_QMAKE_INCLUDE_DIRECTORIES}
DEPENDPATH += ${INSERT_QMAKE_INCLUDE_DIRECTORIES}

SOURCES_APP = ${INSERT_QMAKE_APP_SOURCE_GROUP}
HEADERS_APP = ${INSERT_QMAKE_APP_HEADER_GROUP}
SOURCES_ISO = ${INSERT_QMAKE_ISOAGLIB_SOURCE_GROUP}
HEADERS_ISO = ${INSERT_QMAKE_ISOAGLIB_HEADER_GROUP}

SOURCES += \$\$SOURCES_APP \$\$SOURCES_ISO
HEADERS += \$\$HEADERS_APP \$\$HEADERS_ISO

${INSERT_QMAKE_DEFINITIONS}

${INSERT_QMAKE_LINK_LIBRARIES}
