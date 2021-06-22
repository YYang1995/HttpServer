#include "EventLoop.h"
#include <assert.h>
#include <iostream>
#include <pthread.h>

namespace yy {

__thread EventLoop *t_loopInThisThread = 0;

EventLoop::EventLoop() : looping_(false), threadId_(pthread_self()) {

  poller_=std::make_shared<Poller>(this);
  std::cout << "EventLoop created " << this << " in thread " << threadId_
            << std::endl;
  if (t_loopInThisThread) {
    std::cerr << "Another EvnetLoop " << t_loopInThisThread
              << " exists in this thread\n";
  } else {
    t_loopInThisThread = this;
  }
}
EventLoop::~EventLoop() {
  assert(!looping_);
  t_loopInThisThread = nullptr;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
  return t_loopInThisThread;
}
bool EventLoop::isInLoopThread() { return threadId_ == pthread_self(); }

void EventLoop::loop() {
  assert(!looping_);
  looping_ = true;
  quit_=false;

  while(!quit_){
    activeChannels_.clear();
    poller_->poll(100,&activeChannels_);
    for(auto iter=activeChannels_.begin();iter!=activeChannels_.end();++iter){
      (*iter)->handleEvent();
    }
  }

}

void EventLoop::assertInLoopThread() {
  if (!isInLoopThread()) {
    std::cerr << "assertInLoopThraed() error\n";
    //TODO
//    this->~EventLoop();
  }
}

void EventLoop::quit(){
  quit_=true;

}

void EventLoop::updateChannel(Channel *channel) {
  assert(channel->ownerLoop()== this );
  assertInLoopThread();
  poller_->updateChannel(channel);

}
} // namespace yy