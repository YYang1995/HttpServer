#include "ALog.h"

#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <cstdarg>  //for va_start
#include <iostream>
#include <sstream>

using namespace base;
using namespace std;

LOG_LEVEL ALog::level_ = LOG_LEVEL_INFO;
int ALog::fd_ = -1;
bool ALog::bToFile_ = false;
std::string ALog::logFileName_ = "default";
string ALog::PID_ = "";
LOG_LEVEL ALog::currentLevel_ = LOG_LEVEL_INFO;
list<string> ALog::logList_;
unique_ptr<thread> ALog::writeThread_;
mutex ALog::mtx_;
condition_variable ALog::cv_;
bool ALog::exit_ = false;
bool ALog::running_ = false;

bool ALog::init(const char *logFileName /*=nullptr*/)
{
  if (logFileName == nullptr)
  {
    logFileName_.clear();
  }
  else
  {
    logFileName_ = logFileName;
  }
  PID_ = std::to_string(::getpid());

  // writeThread_.reset(new thread(writeThreadFunc));

  return true;
}

//日志级别，文件名，行号
void ALog::output(LOG_LEVEL level, const char *currentFileName, int lineNo,
                  const char *fmt...)
{
  string log;
  makeLinePrefix(level, log);  //日志级别
  getTime(log);                //时间

  log.push_back('[');
  log.append(std::to_string(pthread_self()));  //线程id
  log.push_back(']');

  log.push_back('[');
  log.append(currentFileName);  //文件名
  log.push_back(']');

  log.append("[line:");
  log.append(std::to_string(lineNo));  //行号
  log.push_back(']');

  log.push_back('[');
  va_list args;
  va_start(args, fmt);
  char msg[1024];
  vsnprintf(msg, sizeof msg, fmt, args);  //格式化消息
  va_end(args);
  log.append(msg);
  log.push_back(']');

  log.append("\r\n"); //换行

  //日志文件名
  char fileName[64];
  time_t now = time(nullptr);
  struct tm *tmNow = gmtime(&now);
  int year = tmNow->tm_year + 1900;
  int month = tmNow->tm_mon + 1;
  int day = tmNow->tm_mday;
  int hour = tmNow->tm_hour + 8;
  int min = tmNow->tm_min;
  // int sec=tmNow->tm_sec;  需不需要秒？
  snprintf(fileName, sizeof fileName, "%4d%02d%02d%02d%02d", year, month,
           day, hour, min);

  string newFileName;
  if (!logFileName_.empty())
  {
    newFileName.append(logFileName_);
    newFileName.append(".");
  }
  newFileName.append(fileName);
  newFileName.append(".");
  newFileName.append(PID_);
  newFileName.append(".log");

  logFileName_.swap(newFileName);

  writeToFile(log);
}

void ALog::makeLinePrefix(LOG_LEVEL level, string &log)
{
  string strLevel = "[INFO]";
  switch (level)
  {
    case LOG_LEVEL_INFO:
      strLevel = "[INFO]";
      break;
    case LOG_LEVEL_ERROR:
      strLevel = "[ERROR]";
      break;
    case LOG_LEVEL_FATAL:
      strLevel = "[FATAL]";
      break;
    default:
      break;
  }
  log.append(strLevel);
}

void ALog::getTime(string &log)
{
  time_t now = time(nullptr);
  struct tm *tmNow = gmtime(&now);
  int year = tmNow->tm_year + 1900;
  int month = tmNow->tm_mon + 1;
  int day = tmNow->tm_mday;
  int hour = tmNow->tm_hour + 8;
  int min = tmNow->tm_min;
  int sec = tmNow->tm_sec;
  char timeArr[32];
  log.push_back('[');
  snprintf(timeArr, sizeof timeArr, "%4d-%02d-%02d %02d:%02d:%02d", year, month,
           day, hour, min, sec);
  log.append(timeArr);
  log.push_back(']');
}

void ALog::writeThreadFunc() {}

bool ALog::writeToFile(const string &data)
{
  const char *msg = data.c_str();
  if (fd_ != -1)
  {
    ::close(fd_);
  }
  //新建文件
  fd_ = open(logFileName_.c_str(), O_CREAT | O_RDWR | O_APPEND, 0666);

  int hasWriten = 0;
  int total = data.size();
  int remaining = total;
  while (remaining > 0)
  {
    int temp = write(fd_, msg, strlen(msg));
    hasWriten += temp;
    remaining = total - hasWriten;
  }
  return true;
}

void ALog::shutdown()
{
  if(fd_!=-1)
  {
    ::close(fd_);
  }
}

void ALog::setLevel(LOG_LEVEL level)
{
  level_=level;
}