#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>

#include "../base/CountDownLatch.h"
#include "../base/Thread.h"
#include "../base/noncopyable.h"
#include "EventLoop.h"


namespace net
{
class EventLoopThread : public base::Thread
{
 public:
  EventLoopThread(std::string name_prefix = "thread");
  ~EventLoopThread();
  virtual void run() override;
  EventLoop* getLoopInThread();

 private:
  EventLoop* loop_;
  base::CountDownLatch latch_;
};
}  // namespace net