#include "Thread.h"

#include <chrono>
#include <functional>
using namespace yy;
using namespace std;

Thread::Thread()
    : started_(false),
      joined_(false),
      thread_(new std::thread(std::bind(&Thread::beginRun, this))) {
}

Thread::~Thread() {
}

void Thread::join() {
  if (!joined_) {
    thread_->join();
    joined_ = true;
  }
}

void Thread::start() {
  unique_lock<std::mutex> lock(mutex_);
  started_ = true;
  cond_.notify_one();
}

bool Thread::isStarted() {
  return started_;
}


void Thread::beginRun() {
  {
    std::unique_lock<std::mutex> lock(mutex_);
    while (!started_) {//该用while or if? 原版用if
      cond_.wait(lock);
    }
  }
  run();
}

void Thread::sleepSecond(const int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

std::thread::id getNowThreadId() {
  return std::this_thread::get_id();
}