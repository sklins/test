TEMPLATE = app
CONFIG += qt console
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

contains ( compiler, clang ) {
    QMAKE_CC = clang
    QMAKE_CXX = clang++
    message("Using Apple CLang C/C++ compiler (clang/clang++)")
} else:contains ( compiler, gnu ) {
    QMAKE_CC = gcc
    QMAKE_CXX = g++
    message("Using GNU C/C++ compiler (gcc/g++)")
} else {
    error("No known C/C++ compiler was specified. Use 'compiler=gnu' or 'compiler=clang' command-line argument.")
}

contains ( warnings, off ) {
    CONFIG += warn_off
    message("Compiler warnings are disabled by user.")
} else {
    message("Compiler warnings are enabled by default. Use 'warnings=off' to disable them.")
}
message()

message("Checking for build type...")
contains ( mode, release ) {
    DEFINES += MODE_RELEASE
    CONFIG += release
    message("Preparing for RELEASE build...")
} else:contains ( mode, debug ) {
    DEFINES += MODE_DEBUG
    CONFIG += debug
    message("Preparing for DEBUG build...")
} else {
    error("No known build mode was specified. Use 'mode=debug' or 'mode=release' command-line argument.")
}

message()

QMAKE_POST_LINK = echo -e \'\\033[1;32mBuild: ok\\033[0;00m\'

INCLUDEPATH += src/
HEADERS += $$system(find src/ -name '*.h')
SOURCES += $$system(find src/ -name '*.cpp')

message("Build makefile is ready, type 'make' to build the project")
message("Qmake: ok")
