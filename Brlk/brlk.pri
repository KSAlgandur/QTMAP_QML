!contains(DEFINES, BRLK) {
message("BRLK loaded");

    DEFINES += BRLK_BFOS

    HEADERS += $$PWD/po_struct.h

    SOURCES +=  $$PWD/po_struct.cpp


    INCLUDEPATH += $$PWD/
}


