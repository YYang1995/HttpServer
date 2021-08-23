#include "EventLoopThread.h"

using namespace net;
using namespace std;
using namespace base;

EventLoopThread::EventLoopThread(std::string name_prefix /*="thread"*/)
    : loop_(nullptr)
{
}

EventLoopThread::~EventLoopThread() {}

void EventLoopThread::run()
{
  EventLoop loop;
  {
    this->loop_ = &loop;
    latch_.signal();
  }
  loop.loop();
}

EventLoop* EventLoopThread::getLoopInThread()
{
  while (loop_ == nullptr)
  {
    latch_.wait();
  }
  return loop_;
}