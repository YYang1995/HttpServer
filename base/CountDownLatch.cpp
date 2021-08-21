#include "CountDownLatch.h"

#include <memory>

using namespace base;
using namespace std;

CountDownLatch::CountDownLatch(int count /*=1*/)
    : mutex_(), cond_(), count_(count)
{
}

CountDownLatch::~CountDownLatch() {}

void CountDownLatch::wait()
{
  std::unique_lock<std::mutex> lock(mutex_);
  while (count_ > 0)
  {
    cond_.wait(lock);
  }
  lock.unlock();
}

void CountDownLatch::signal()
{
  std::lock_guard<std::mutex> guard(mutex_);
  --count_;
  if (count_ == 0)
  {
    cond_.notify_all();
  }
}