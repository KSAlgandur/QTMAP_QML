 

!contains(DEFINES, PEX) {
message("PEX loaded");

    DEFINES += BRLK_BFOS

    HEADERS += $$PWD/coefficients.h \
                $$PWD/pex429.h \
                $$PWD/pex429LNX.h \
                $$PWD/pex429LNXmacro.h \
                $$PWD/readparamdispatcher.h \
                $$PWD/signalhandlerdispatcher.h


    SOURCES +=  $$PWD/pex429.cpp \
                $$PWD/readparamdispatcher.cpp \
                $$PWD/signalhandlerdispatcher.cpp


    INCLUDEPATH += $$PWD/
}
