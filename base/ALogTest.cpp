#include <cstdarg>
#include <iostream>
#include <string>

#include "ALog.cpp"
#include "ALog.h"

using namespace base;
using namespace std;

#define LOG_INFO(...) \
  ALog::output(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)

int main()
{
  ALog::init("logs/");
  string now;
  LOG_INFO("hello ALog!\n");
  sleep(1);
  LOG_INFO("%d%02d",1,2);
}