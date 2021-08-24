#include "EventLoopThreadPool.h"

using namespace net;
using namespace std;

EventLoopThreadPool::EventLoopThreadPool(EventLoop* loop)
    : mainLoop_(loop), started_(false), threadNum_(0), threadIndex_(0)
{
}

void EventLoopThreadPool::init(int num)
{
  threadNum_ = num;
  for (int i = 0; i < threadNum_; i++)
  {
    std::shared_ptr<EventLoopThread> thread(new EventLoopThread("workThread"+std::to_string(i+1)));

    thread->start();
    threadPool_.push_back(thread);

    eventLoopPool_.push_back(thread->getLoopInThread());
  }
  started_ = true;
}

bool EventLoopThreadPool::isStarted() { return started_; }

EventLoop* EventLoopThreadPool::getOneLoopFromPool()
{
  if (eventLoopPool_.empty())
  {
    return mainLoop_;
  }
  threadIndex_ = (threadIndex_ + 1) % threadNum_;
  return eventLoopPool_[threadIndex_];
}
