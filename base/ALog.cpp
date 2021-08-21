#include "ALog.h"

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>  //for umask
#include <time.h>
#include <unistd.h>

#include <condition_variable>
#include <cstdarg>  //for va_start
#include <functional>
#include <iostream>
#include <mutex>

using namespace base;
using namespace std;

LOG_LEVEL ALog::level_ = LOG_LEVEL_INFO;
int ALog::fd_ = -1;
bool ALog::bToFile_ = true;  //默认写入文件
std::string ALog::logFileName_ = "default";
std::string ALog::logFilePath_ = "logs/";
string ALog::PID_ = "";
LOG_LEVEL ALog::currentLevel_ = LOG_LEVEL_INFO;
list<string> ALog::logList_;
unique_ptr<std::thread> ALog::writeThread_;
// std::mutex ALog::mutex_;
// std::condition_variable ALog::cond_;
pthread_mutex_t ALog::mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ALog::cond_ = PTHREAD_COND_INITIALIZER;
bool ALog::exit_ = false;
bool ALog::running_ = false;

bool ALog::init(const char *logFilePath /*=nullptr*/, bool bToFile /* =true*/)
{
  bToFile_ = bToFile;
  if(!bToFile)
  {
    fd_ = STDOUT_FILENO;
  }
  running_ = true;
  if (logFilePath == nullptr)
  {
    // logFilePath_.clear();
  }
  else
  {
    logFilePath_ = logFilePath;
  }
  PID_ = std::to_string(::getpid());

  writeThread_.reset(new thread(std::bind(ALog::writeThreadFunc)));
  return true;
}

//日志级别，文件名，行号
void ALog::output(LOG_LEVEL level, const char *currentFileName, int lineNo,
                  const char *fmt...)
{
  //生成log内容
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

  log.append("\r\n");  //换行

  //日志文件名,每个小时或重启程序就更新一个日志文件名
  char fileName[64];
  time_t now = time(nullptr);
  struct tm *tmNow = gmtime(&now);
  int year = tmNow->tm_year + 1900;
  int month = tmNow->tm_mon + 1;
  int day = tmNow->tm_mday;
  int hour = tmNow->tm_hour + 8;
  // int min = tmNow->tm_min;
  snprintf(fileName, sizeof fileName, "%4d%02d%02d%02d", year, month, day,
           hour);

  string newFileName;
  newFileName.append(logFilePath_);
  newFileName.append(fileName);
  newFileName.append(".");
  newFileName.append(PID_);
  newFileName.append(".log");
  if (!logFileName_.empty())
  {
    logFileName_.clear();
  }
  logFileName_.swap(newFileName);

  if (!createLogFile())
  {
    return;
  }
  {
    // std::lock_guard<std::mutex> guard(mutex_);
    pthread_mutex_lock(&mutex_);
    logList_.push_back(log);
    pthread_mutex_unlock(&mutex_);
    // cond_.notify_one();
    pthread_cond_signal(&ALog::cond_);
  }
}

bool ALog::createLogFile()
{
  //已有文件或写入控制台,则直接写入
  if (fd_ > 0)
  {
    return true;
  }
  //新建文件
  umask(0002);
  fd_ = open(logFileName_.c_str(), O_CREAT | O_RDWR | O_APPEND, 0666);
  if (fd_ == -1)
  {
    cout << "fd==-1 " << strerror(errno) << endl;
    return false;
  }
  return true;
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

void ALog::writeThreadFunc()
{
  // std::lock_guard<std::mutex> guard(mutex_);
  string log;
  while (running_)
  {
    pthread_mutex_lock(&ALog::mutex_);
    while (logList_.empty())
    {
      // cond_.wait();
      pthread_cond_wait(&ALog::cond_, &ALog::mutex_);
    }

    while (!logList_.empty())
    {
      log = logList_.front();
      logList_.pop_front();
      writeToFile(log.c_str());
    }
    pthread_mutex_unlock(&ALog::mutex_);
  }
}

bool ALog::writeToFile(const string &data)
{
  const char *msg = data.c_str();

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
  running_ = false;
  pthread_cond_signal(&cond_);  //最后一次唤醒被阻塞的writeThread
  exit_ = true;
  if (writeThread_->joinable())
  {
    writeThread_->join();
  }
  if (fd_ != -1 && fd_ != STDOUT_FILENO)
  {
    ::close(fd_);
  }
}

void ALog::setLevel(LOG_LEVEL level) { level_ = level; }