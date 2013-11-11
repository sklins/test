TEMPLATE = app
CONFIG += qt console warn_off
QT = core

OBJECTS_DIR = obj/
MOC_DIR = moc/
DESTDIR = bin/
TARGET = femu

message("Starting femu (qmake) build system")
message()

message("Checking for QT...")
message("Qt version:          $$[QT_VERSION]")
message("Qt is installed in:  $$[QT_INSTALL_PREFIX]")
message()

message("Checking for C/C++ compiler...")

contains ( COMPILER, CLANG ) {
    QMAKE_CC = clang
    QMAKE_CXX = clang++
    message("Using Apple CLang C/C++ compiler (clang/clang++)")
} else:contains ( COMPILER, GCC ) {
    QMAKE_CC = gcc
    QMAKE_CXX = g++
    message("Using GNU C/C++ compiler (gcc/g++)")
} else {
    error("No known C/C++ compiler was specified. Use 'COMPILER=GCC' or 'COMPILER=CLANG' command-line argument.")
}
message()

message("Checking for build type...")
contains ( MODE, RELEASE ) {
    DEFINES += MODE_RELEASE
    CONFIG += release
    message("Preparing for RELEASE build...")
} else:contains ( MODE, DEBUG ) {
    DEFINES += MODE_DEBUG
    CONFIG += debug
    message("Preparing for DEBUG build...")
} else {
    error("No known build mode was specified. Use 'MODE=DEBUG' or 'MODE=RELEASE' command-line argument.")
}

message()

QMAKE_POST_LINK = echo -e \'\\033[1;32mBuild: ok\\033[0;00m\'

INCLUDEPATH += src/
HEADERS += $$system(find src/ -name '*.h')
SOURCES += $$system(find src/ -name '*.cpp')

message("Build makefile is ready, type 'make' to build the project")
message("Qmake: ok")
