#include "Thread.h"

#include <assert.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/prctl.h>

#include <chrono>
#include <functional>
#include <iostream>


using namespace base;
using namespace std;

Thread::Thread(string name_prefix /*="thread"*/)
    : name_prefix_(name_prefix),
      started_(false),
      joined_(false),
      thread_(nullptr),
      latch_(1)
{
}

Thread::~Thread()
{
  if (started_ && !joined_)
  {
    started_ = false;
    thread_->detach();
  }
}
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
  assert(started_ == false);
  thread_.reset(new thread(std::bind(&Thread::beginRun, this)));
  latch_.wait();
  assert(threadId_ > 0);  //表明线程创建成功
}

bool Thread::isStarted() { return started_; }

void Thread::beginRun()
{
  started_ = true;
  threadId_ = pthread_self();
  tid_ = static_cast<pid_t>(syscall(SYS_gettid));
  name_=name_prefix_+"/"+std::to_string(tid_);
  //主线程不可以设置线程名，防止killall崩溃
  if(tid_!=getpid())
  {
    int err = prctl(PR_SET_NAME, name_prefix_.c_str());  //传入c风格字符串
    if(err<0)
    {
      cout<<"prctl error\n";
    }
  }
  latch_.signal();
  run();
}

void Thread::sleepSecond(const int seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

string Thread::getName() const 
{
  return name_;
}

string Thread::getNamePrefix() const
{
  return name_prefix_;
}

pthread_t Thread::getThreadId()
{
  return threadId_;
}

