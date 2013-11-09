TEMPLATE = app
CONFIG += qt console debug warn_off
QT = core

OBJECTS_DIR = obj/
MOC_DIR = moc/
DESTDIR = bin/
TARGET = femu

DEFINES += MODE_DEBUG

INCLUDEPATH += src/
HEADERS += $$system(find src/ -name '*.h')
SOURCES += $$system(find src/ -name '*.cpp')
