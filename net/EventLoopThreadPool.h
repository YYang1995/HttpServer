#pragma once
#include <memory>
#include <vector>

#include "EventLoopThread.h"

namespace net
{
class EventLoopThreadPool
{
 public:
  EventLoopThreadPool(EventLoop *loop);
  void init(int num = 8);
  bool isStarted();
  EventLoop *getOneLoopFromPool();  //轮询？
 private:
  EventLoop *mainLoop_;
  bool started_;
  uint16_t threadNum_;
  uint32_t threadIndex_;
  std::vector<std::shared_ptr<EventLoopThread>> threadPool_;
  std::vector<EventLoop *> eventLoopPool_;
};
}  // namespace net