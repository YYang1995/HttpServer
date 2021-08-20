#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include "CountDownLatch.h"

namespace base
{
class Thread
{
 public:
  Thread();
  ~Thread();
  void start();  //线程启动前的准备工作，用来唤醒beginRun();
  bool isStarted();
  void join();
  pthread_t getNowThreadId()
  {
    return threadId_;
  }
  virtual void run() = 0;

 protected:
  void sleepSecond(const int seconds);

 private:
  void beginRun();  //线程入口函数

  bool started_;
  bool joined_;
  pthread_t threadId_;
  pid_t tid_;
  CountDownLatch latch_;
  std::shared_ptr<std::thread> thread_; //which smart pointer?
};
}  // namespace yy