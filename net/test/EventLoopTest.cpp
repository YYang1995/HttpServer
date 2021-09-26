#include <iostream>

#include "../../base/ALog.h"
#include "../../net/EventLoop.h"

using namespace base;
using namespace std;
using namespace net;

int main()
{
  ALog::init(nullptr,false);

  EventLoop loop;
  loop.loop();

  ALog::shutdown();
}