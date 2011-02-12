# Archivo generado por el gestor qmake de kdevelop.
# -------------------------------------------
# Subdirectorio relativo al directorio principal del proyecto: ./src
# El destino es una aplicaci??n: ../bin/qantenna

QANTENNA_VERSION = trunk
DEFINES += QANTENNA_VERSION=\\\"$${QANTENNA_VERSION}\\\"

UI_DIR = ui
FORMS += ui/mainwindowqantenna.ui \
         ui/about.ui

TRANSLATIONS += ../qt/ts/qantenna_da.ts \
                ../qt/ts/qantenna_de.ts \
                ../qt/ts/qantenna_es.ts \
                ../qt/ts/qantenna_fr.ts \
                ../qt/ts/qantenna_it.ts \
                ../qt/ts/qantenna_nl.ts \
                ../qt/ts/qantenna_pl.ts \
                ../qt/ts/qantenna_ru.ts \
                ../qt/ts/qantenna_sv.ts \
                ../qt/ts/qantenna_uk.ts

HEADERS += gl.h \
           camera.h \
           datamanager.h \
           glwidget.h \
           line.h \
           ui/mainwindow.h \
           ui/about.h \
           neccontainer.h \
           necinput.h \
           necinputparser.h \
           necoutput.h \
           necoutputparser.h \
           patch.h \
           primitive.h \
           radiationpattern.h \
           loadthread.h \
           antennadelegate.h \
           mmath.h \
           vec3.h \
 \
 point4f.h \
 vertexmatrix.h
SOURCES += gl.cpp \
           camera.cpp \
           datamanager.cpp \
           glwidget.cpp \
           line.cpp \
           main.cpp \
           ui/mainwindow.cpp \
           ui/about.cpp \
           neccontainer.cpp \
           necinput.cpp \
           necinputparser.cpp \
           necoutput.cpp \
           necoutputparser.cpp \
           patch.cpp \
           radiationpattern.cpp \
           loadthread.cpp \
           antennadelegate.cpp \
           mmath.cpp \
           vec3.cpp \
 \
 point4f.cpp \
 vertexmatrix.cpp
RESOURCES = resource.qrc
TARGET = qantenna
DESTDIR = ../bin/
CONFIG += opengl thread warn_on

# Default defines values
EXAMPLES_PATH = ""

unix {
    CONFIG += debug
    # Prefix: base instalation directory
    isEmpty( PREFIX ){
        PREFIX = /usr/local
    }

    DEB_BUILD = $$system(echo \$DEB_BUILD_OPTIONS)
    contains(DEB_BUILD, nostrip){
        QMAKE_STRIP =:
    }

    DEFINES += PREFIX=\\\"$${PREFIX}\\\"
    target.path = $${PREFIX}/bin
    INSTALLS = target

    # Translations
    translations.path = $${PREFIX}/share/qantenna
    translations.files = \
    ../qt/ts/qantenna_da.qm \
    ../qt/ts/qantenna_de.qm \
    ../qt/ts/qantenna_es.qm \
    ../qt/ts/qantenna_fr.qm \
    ../qt/ts/qantenna_it.qm \
    ../qt/ts/qantenna_nl.qm \
    ../qt/ts/qantenna_pl.qm \
    ../qt/ts/qantenna_ru.qm \
    ../qt/ts/qantenna_sv.qm

    INSTALLS += translations

    # Examples
    EXAMPLES_PATH = $${PREFIX}/share/doc/qantenna/examples
    examples.path = $${EXAMPLES_PATH}
    examples.files = ../examples/*
    INSTALLS += examples
}

win32 {
    CONFIG += release
    INCLUDEPATH = .
    RC_FILE = ../distrib/win32/icon.rc
}

# Set the values of the defines
DEFINES += EXAMPLES_PATH=\\\"$${EXAMPLES_PATH}\\\"

TEMPLATE = app
QT += opengl
#LIBS += -lGLEW

# Sub-directories
UI_DIR = ../qt/uic
MOC_DIR = ../qt/moc
OBJECTS_DIR = ../qt/obj
RCC_DIR = ../qt/res

# Cards lib
LIBS += ../qt/lib/libQAntennaCards.a
TARGETDEPS += ../qt/lib/libQAntennaCards.a
