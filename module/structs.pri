!contains(DEFINES, po_structs) {
message("po_structs loaded");

    DEFINES += BRLK_BFOS

    HEADERS +=  $$PWD/po_struct.h \


    SOURCES +=  $$PWD/


    INCLUDEPATH += $$PWD/
}

