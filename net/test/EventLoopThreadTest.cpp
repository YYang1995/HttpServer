#include "../EventLoopThread.h"
#include <iostream>

using namespace std;
using namespace net;

int main()
{
  EventLoopThread eventLoopthread;
  eventLoopthread.start();
  eventLoopthread.join();
}