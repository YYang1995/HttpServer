#include "Thread.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <sys/syscall.h>
#include <unistd.h>

using namespace base;
using namespace std;

Thread::Thread() : started_(false), joined_(false), thread_(nullptr), latch_(1)
{
}

Thread::~Thread() {}

void Thread::join()
{
  if (!joined_)
  {
    thread_->join();
    joined_ = true;
  }
}

void Thread::start()
{
  thread_.reset(new thread(std::bind(&Thread::beginRun, this)));
  latch_.wait();
}

bool Thread::isStarted() { return started_; }

void Thread::beginRun()
{
  started_ = true;
  threadId_=pthread_self();
  tid_=static_cast<pid_t>(syscall(SYS_gettid));

  latch_.signal();
  run();
}

void Thread::sleepSecond(const int seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// std::thread::id getNowThreadId() { return std::this_thread::get_id(); }