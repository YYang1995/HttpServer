#include <cstdarg>
#include <iostream>
#include <string>
#include <signal.h>

#include "../ALog.h"
#include "../ALog.cpp"
using namespace base;
using namespace std;

void server_exit(int signo)
{
  cout<<"Server receive signal "<<signo<<" to exit \n";
  ALog::shutdown();
}
int main()
{
  signal(SIGINT,server_exit);

  ALog::init(nullptr, false);  //写道控制台
  // ALog::init("logs/", true);
  LOG_INFO("hello ALog");
  LOG_ERROR("hello ALog");
  LOG_FATAL("hello ALog");
  ALog::shutdown();
}