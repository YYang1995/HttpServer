#include <iostream>

#include "../EventLoopThread.h"
#include "../../base/ALog.h"

using namespace base;
using namespace std;
using namespace net;

int main()
{
  ALog::init(nullptr,false);
  EventLoopThread eventLoopthread;
  eventLoopthread.start();
  eventLoopthread.join();
  ALog::shutdown();
}