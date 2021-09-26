#include "EventLoop.h"

#include <assert.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <iostream>

#include "../base/ALog.h"
#include "Channel.cpp"
#include "Epoll.h"
#include "Epoll.cpp"

using namespace base;
using namespace std;
using namespace net;

namespace net
{
__thread EventLoop *t_loopInThisThread = 0;

EventLoop::EventLoop()
    : looping_(false),
      threadId_(pthread_self()),
      activeChannels_(16),  
      poller_(std::make_unique<Epoll>(this))
{
  wakeupFd_=eventfd(0, EFD_NONBLOCK);
  wakeupChannel_.reset(new Channel(this, wakeupFd_));
  if(wakeupFd_==-1)
  {
    LOG_ERROR("EventLoop::EventLoop() wakeupFd_ error");
  }

  LOG_INFO("EventLoop created %ld in thread ", this, threadId_);

  if (t_loopInThisThread)
  {
    LOG_ERROR("Another EvnetLoop %d exists in this thread", t_loopInThisThread);
  }
  else
  {
    t_loopInThisThread = this;
    wakeupChannel_->setReadCallback(
        std::bind(&EventLoop::handleWakeupRead, this));
    wakeupChannel_->enableReading();
  }
}
EventLoop::~EventLoop()
{
  assert(!looping_);
  t_loopInThisThread = nullptr;
  wakeupChannel_->disableAll();
  wakeupChannel_->remove();
  ::close(wakeupFd_);
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
         iter++)
    {
      currentActiveChannel_=*iter;
      currentActiveChannel_->handleEvent();
    }
    currentActiveChannel_=nullptr;
    doPendingFunctors();
  }
  looping_ = false;
  // LOG_INFO("EventLoop stop looping.");
}
void EventLoop::runInLoop(Functor cb)
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
  uint64_t one = 1;
  int len = write(wakeupFd_, &one, sizeof one);
  if (len != sizeof one)
  {
    // LOG_ERROR("EventLoop::wakeup() error! Actually %d bytes were writen", len);
  }
}
void EventLoop::assertInLoopThread()
{
  if (!isInLoopThread())
  {
    // LOG_FATAL("EventLoop::assertInLoopThread() error. ");
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

void EventLoop::removeChannel(Channel *channel)
{
  assertInLoopThread();
  poller_->removeChannel(channel);
}

void EventLoop::queueInLoop(Functor cb)
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    // pendingFunctors.push_back(std::move(cb));
    pendingFunctors.push_back(cb);
    // cout<<"pendingFucntors.size()= "<<pendingFunctors.size()<<endl;
    // cout<<"pendingFucntors.capacity()= "<<pendingFunctors.capacity()<<endl;
  }
  if (!isInLoopThread() || callingPendingFunctors_)
  {
    wakeup();
  }
}

void EventLoop::handleWakeupRead()
{
  uint64_t one;
  ssize_t len = read(wakeupFd_, &one, sizeof one);
  if (len != sizeof one)
  {
    // LOG_ERROR("EventLoop::handleWakeupRead() error");
  }
}

}  // namespace net