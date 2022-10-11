#include "readparamdispatcher.h"

pex429* Readparamdispatcher::_reader = nullptr;

void Readparamdispatcher::setReader(pex429 * reader) {_reader = reader;}

void Readparamdispatcher::saReader(int v){_reader ->ReadDataFromPEX(v);}
