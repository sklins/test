#pragma once
#include <QtCore>
#include <assert.h>

#define FAIL qFatal

#define MESSAGE(msg) \
    QTextStream(stderr) << msg << "\n"

#ifdef MODE_DEBUG
#   define DEBUG_MESSAGE(msg) MESSAGE(msg)
#else
#   define DEBUG_MESSAGE(msg)
#endif

#define ASSERT assert
