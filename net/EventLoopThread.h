#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>

#include "../base/Thread.h"
#include "../base/noncopyable.h"
#include "EventLoop.h"

namespace yy {
class EventLoopThread : public yy::Thread {
public:
  EventLoopThread();
  ~EventLoopThread();
  virtual void run() override;
  EventLoop* getLoopInThread();

private:
  EventLoop* loop_;
  std::mutex mtx_;
  std::condition_variable cond_;
};
}// namespace yy