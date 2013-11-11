TEMPLATE = app
CONFIG += qt console debug warn_off
QT = core

OBJECTS_DIR = obj/
MOC_DIR = moc/
DESTDIR = bin/
TARGET = femu

DEFINES += MODE_DEBUG

QMAKE_POST_LINK = echo -e \'\\033[1;32mBuild: ok\\033[0;00m\'

INCLUDEPATH += src/
HEADERS += $$system(find src/ -name '*.h')
SOURCES += $$system(find src/ -name '*.cpp')
