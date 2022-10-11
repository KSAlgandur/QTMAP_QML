#ifndef SIGNALHANDLERDISPATCHER_H
#define SIGNALHANDLERDISPATCHER_H

#include "pex429.h"

class pex429;

class SignalHandlerDispatcher {
private:
  static pex429* _handler;

public:
  static void setHandler(pex429* handler);
  static void saHandler(int v);
};
#endif // SIGNALHANDLERDISPATCHER_H
