!contains(DEFINES, UDP) {
message("UDP loaded");

    DEFINES += BRLK_BFOS

    HEADERS += $$PWD/qudpsocketcat.hpp

    SOURCES +=  $$PWD/qudpsocketcat.cpp


    INCLUDEPATH += $$PWD/
}

HEADERS += \
    $$PWD/qudpsocketcat.h


