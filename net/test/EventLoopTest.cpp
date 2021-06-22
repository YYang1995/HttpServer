#include <unistd.h>
#include <string.h>


#include <iostream>

#include "../EventLoop.h"
#include <sys/timerfd.h>

using namespace yy;
using namespace std;
EventLoop *g_loop;
void timeout() {
 printf("Timeout\n");
 g_loop->quit();
}
void f(){
  cout<<"in f()\n";
}
int main() {
  EventLoop loop;
  g_loop=&loop;

  int timerfd=timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK|TFD_CLOEXEC);
  Channel channel(&loop,timerfd);
  channel.setReadCallback(timeout);
  channel.enableReading();
  Poller poller(&loop);

  struct itimerspec howlong;
  bzero(&howlong,sizeof howlong);
  howlong.it_value.tv_sec=5;
  ::timerfd_settime(timerfd,0,&howlong, nullptr);

  loop.loop();

  ::close(timerfd);
}
