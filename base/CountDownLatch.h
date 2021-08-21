#pragma once

#include <condition_variable>
#include <mutex>

namespace base
{
class CountDownLatch
{
 public:
  CountDownLatch(int count = 1);
  ~CountDownLatch();
  void wait();
  void signal();

 private:
  std::condition_variable cond_;
  std::mutex mutex_;
  int count_;
};
}  // namespace base