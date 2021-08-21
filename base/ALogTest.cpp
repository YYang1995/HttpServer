#include <cstdarg>
#include <iostream>
#include <string>

#include "ALog.cpp"
#include "ALog.h"

using namespace base;
using namespace std;

int main()
{
  ALog::init(nullptr,false);//写道控制台
  // ALog::init("logs/", true);
  for (int i = 0; i < 5; i++)
  {
    sleep(1);
    LOG_INFO("hello ALog!");
    LOG_ERROR("?");
    LOG_FATAL("1+2=%d", 3);
  }
  ALog::shutdown();
}