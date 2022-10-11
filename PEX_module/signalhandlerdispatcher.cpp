#include "signalhandlerdispatcher.h"

pex429* SignalHandlerDispatcher::_handler = nullptr;

void SignalHandlerDispatcher::setHandler(pex429* handler) { _handler = handler; }

void SignalHandlerDispatcher::saHandler(int v) { _handler->hINT(v); }
