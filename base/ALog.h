#pragma once

#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include "Thread.h"

namespace base
{
enum LOG_LEVEL
{
  LOG_LEVEL_INFO,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_FATAL
};

class ALog
{
 public:
  ALog() = delete;
  ~ALog() = delete;
  ALog(const ALog &) = delete;
  ALog &operator=(const ALog &) = delete;

  static bool init(const char *logFilePath = nullptr, bool bToFile = true);
  static void shutdown();
  static void output(LOG_LEVEL level, const char *fileName, int linNo,
                     const char *fmt, ...);
  static void makeLinePrefix(LOG_LEVEL level, std::string &log);
  static void getTime(std::string &log);
  static bool writeToFile(const std::string &data);
  static void setLevel(LOG_LEVEL level);
  static bool createLogFile();

 private:
  static void writeThreadFunc();  //写线程入口函数

  static LOG_LEVEL level_;
  static int fd_;
  static bool bToFile_;  //写到文件还是控制台,true为写入文件
  static std::string logFileName_;
  static std::string logFilePath_;
  static std::string PID_;
  static LOG_LEVEL currentLevel_;          //当前日志level
  static std::list<std::string> logList_;  //待写入的日志列表
  static std::unique_ptr<std::thread> writeThread_;
  // static std::mutex mutex_;
  // static std::condition_variable cond_;
  static pthread_mutex_t mutex_;
  static pthread_cond_t cond_;
  static bool exit_;     //退出标志
  static bool running_;  //运行标志
};

#define LOG_INFO(...) \
  ALog::output(LOG_LEVEL::LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) \
  ALog::output(LOG_LEVEL::LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) \
  ALog::output(LOG_LEVEL::LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
}  // namespace base
