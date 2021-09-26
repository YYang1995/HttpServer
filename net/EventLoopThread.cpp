#include "EventLoopThread.h"

using namespace net;
using namespace std;
using namespace base;

EventLoopThread::EventLoopThread(std::string name_prefix /*="thread"*/)
    : loop_(nullptr), mtx_()
{
}

EventLoopThread::~EventLoopThread()
{
  loop_->quit();
  join();
}

void EventLoopThread::destroy()
{
  if(loop_!=nullptr)
  {
    loop_->quit();
  }
  base::Thread::join();
}

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
  EventLoop* loop = nullptr;   //返回一个copy
  {
    // std::lock_guard<std::mutex> guard(mtx_);
    while (loop_ == nullptr)
    {
      latch_.wait();
    }
    loop=loop_;
  }

  return loop;
}