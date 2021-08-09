#include "EventLoop.h"

#include <assert.h>
#include <pthread.h>

#include <iostream>
#include "Epoll.h"

namespace yy
{
__thread EventLoop *t_loopInThisThread = 0;

EventLoop::EventLoop() : looping_(false), threadId_(pthread_self())
{
  poller_ = std::make_shared<Epoll>(this);
  std::cout << "EventLoop created " << this << " in thread " << threadId_
            << std::endl;
  if (t_loopInThisThread)
  {
    std::cerr << "Another EvnetLoop " << t_loopInThisThread
              << " exists in this thread\n";
  }
  else
  {
    t_loopInThisThread = this;
  }
}
EventLoop::~EventLoop()
{
  assert(!looping_);
  t_loopInThisThread = nullptr;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread()
{
  return t_loopInThisThread;
}
bool EventLoop::isInLoopThread() { return threadId_ == pthread_self(); }

void EventLoop::loop()
{
  assert(!looping_);
  looping_ = true;
  quit_ = false;

  while (!quit_)
  {
    activeChannels_.clear();
    poller_->poll(100, &activeChannels_);
    for (auto iter = activeChannels_.begin(); iter != activeChannels_.end();
         ++iter)
    {
      (*iter)->handleEvent();
    }
    doPendingFunctors();
  }
  looping_ = false;
}
void EventLoop::runInLoop(const Functor &cb)
{
  if (isInLoopThread())
  {
    cb();
  }
  else
  {
    queueInLoop(cb);
  }
}
void EventLoop::doPendingFunctors()
{
  std::vector<Functor> functors;
  callingPendingFunctors_ = true;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    functors.swap(pendingFunctors);
  }
  for (size_t i = 0; i < functors.size(); i++)
  {
    functors[i]();
  }
  callingPendingFunctors_ = false;
}
void EventLoop::wakeup()
{
  // TODO
}
void EventLoop::assertInLoopThread()
{
  if (!isInLoopThread())
  {
    // std::cerr << "thread id ="<<loop;
    // TODO
    //    this->~EventLoop();
  }
}

void EventLoop::quit()
{
  quit_ = true;
  if (!isInLoopThread())
  {
    wakeup();
  }
}

void EventLoop::updateChannel(Channel *channel)
{
  assert(channel->ownerLoop() == this);
  assertInLoopThread();
  poller_->updateChannel(channel);
}
}  // namespace yy