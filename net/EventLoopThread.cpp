#include "EventLoopThread.h"

using namespace yy;
EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
    : loop_(nullptr),
      existing_(false),
      mutex_(),
      cond_(),
      callback_(cb),
      thread_(std::bind(&EventLoopThread::threadFunc, this)) {}

EventLoopThread::~EventLoopThread() {
  existing_=true;
  if(loop_!= nullptr){
    loop_->quit();
    thread_.join();
  }
}

EventLoop* EventLoopThread::startLoop() {

}