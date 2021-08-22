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
  ALog::shutdown();
}