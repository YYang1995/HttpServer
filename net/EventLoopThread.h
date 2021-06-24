#pragma once
#include <condition_variable>
#include <functional>
#include <string>
#include <thread>

#include "../base/noncopyable.h"
#include "EventLoop.h"

namespace yy {
class EventLoopThread : noncopyable {
public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;

  EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),
                  const std::string& name = std::string());
  ~EventLoopThread();
  EventLoop* startLoop();

private:
  void threadFunc();
  EventLoop* loop_;
  bool existing_;
  std::thread thread_;//与muduo不同
  std::mutex mutex_;
  std::condition_variable cond_;//与muduo不同;
  ThreadInitCallback callback_;
};
}// namespace yy