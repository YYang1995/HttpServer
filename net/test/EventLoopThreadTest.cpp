#include "../EventLoopThread.h"
#include <iostream>

using namespace std;
using namespace yy;

int main()
{
  EventLoopThread eventLoopthread;
  eventLoopthread.start();
  eventLoopthread.join();
}