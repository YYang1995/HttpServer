#include "EventLoopThread.h"

using namespace yy;
using namespace std;

EventLoopThread::EventLoopThread():loop_(nullptr) {

}

EventLoopThread::~EventLoopThread() {

}

void EventLoopThread::run() {
  EventLoop loop;
  {
    std::unique_lock<std::mutex> lock(mtx_);
    this->loop_=&loop;
    cond_.notify_one();
  }
  loop.loop();
}

EventLoop* EventLoopThread::getLoopInThread() {
  this->start();  //必不可少，原版少了此行;这一行的位置？
  {
    unique_lock<std::mutex> lock(mtx_);
    while(loop_== nullptr){
      cond_.wait(lock);
    }
  }
  return loop_;
}