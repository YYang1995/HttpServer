#pragma once

#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

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
  ALog(const ALog&) = delete;
  ALog& operator=(const ALog&) = delete;

  static bool init(const char *logFileName =nullptr);
  static void shutdown();
  static void output(LOG_LEVEL level,const char *fileName,int linNo,const char *fmt,...);
  static void writeThreadFunc(); //写线程入口函数
  static void makeLinePrefix(LOG_LEVEL level,std::string &log);
  static void getTime(std::string &log);
  static bool writeToFile(const std::string &data);
  static void setLevel(LOG_LEVEL level);

 private:
  static LOG_LEVEL level_;
  static int fd_;
  static bool bToFile_;  //写到文件还是控制台
  static std::string logFileName_;
  static std::string PID_;
  static LOG_LEVEL currentLevel_;          //当前日志level
  static std::list<std::string> logList_;  //待写入的日志列表
  static std::unique_ptr<std::thread> writeThread_;
  static std::mutex mtx_;
  static std::condition_variable cv_;
  static bool exit_;     //退出标志
  static bool running_;  //运行标志
};
}  // namespace base
