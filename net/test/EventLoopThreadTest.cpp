#include "../EventLoopThread.h"
#include <iostream>
#include "../Socket.h"
#include "../Channel.h"
#include <sys/timerfd.h>
#include <string.h>

using namespace yy;
using namespace std;

EventLoop *g_loop;
void timeout() {
  printf("Timeout\n");
  g_loop->quit();
}
int main()
{

  EventLoopThread eventLoopThread;

   g_loop=eventLoopThread.getLoopInThread();

  int timerfd=timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);
  Channel channel(g_loop,timerfd);
  channel.setReadCallback(timeout);
  channel.enableReading();

  struct itimerspec howlong;
  bzero(&howlong,sizeof howlong);
  howlong.it_value.tv_sec=5;
  ::timerfd_settime(timerfd,0,&howlong, nullptr);

  eventLoopThread.run();
}