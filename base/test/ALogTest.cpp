#include <iostream>
#include <string>

#include "../ALog.cpp"
#include "../ALog.h"

using namespace base;
using namespace std;

int main()
{
  ALog::init();
  string now;
  ALog::output(LOG_LEVEL_INFO, __FILE__, __LINE__, "%d-%2d", 99, 2);
  sleep(1);
  ALog::output(LOG_LEVEL_INFO, __FILE__, __LINE__, "%d-%2d", 123, 88);
}