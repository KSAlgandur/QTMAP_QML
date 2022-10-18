!contains(DEFINES, GENERATOR ) {
message("GENERATOR loaded");

    DEFINES += BRLK_BFOS

    HEADERS += $$PWD/generator.hpp

    SOURCES +=  $$PWD/generator.cpp


    INCLUDEPATH += $$PWD/
}

HEADERS += \
    $$PWD/generator.h


