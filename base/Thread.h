#pragma once
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>

namespace yy{
class Thread{
public:
  Thread();
  ~Thread();
  void start();  //线程启动前的准备工作，用来唤醒beginRun();
  static std::thread::id getNowThreadId();  //这里有链接错误 TODO
  bool isStarted();
  void join();
  virtual void run()=0;
protected:
  void sleepSecond(const int seconds);
private:
  void beginRun();  // //线程入口函数,;
  bool started_;
  bool joined_;
  std::mutex mutex_;
  std::condition_variable cond_;
  std::shared_ptr<std::thread> thread_;
};
}