#ifndef READPARAMDISPATCHER_H
#define READPARAMDISPATCHER_H


#include "pex429.h"

class pex429;

class Readparamdispatcher
{
private:
    static pex429* _reader;

public:
    static void setReader(pex429* reader);
    static void saReader(int v);
};

#endif // READPARAMDISPATCHER_H
