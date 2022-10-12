 
!contains(DEFINES, PARSER) {
message("PARSER loaded");

    DEFINES += BRLK_BFOS

    HEADERS += $$PWD/parser.h


    SOURCES +=  $$PWD/parser.cpp


    INCLUDEPATH += $$PWD/
}

