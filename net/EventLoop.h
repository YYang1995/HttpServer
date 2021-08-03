#pragma once
#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "../base/noncopyable.h"
#include "Channel.h"
#include "Poller.h"

namespace yy
{
class Channel;
class Poller;
class EventLoop : public noncopyable
{
 public:
  typedef std::function<void()> Functor;
  EventLoop();
  ~EventLoop();

  void loop();

  bool isInLoopThread();
  EventLoop *getEventLoopOfCurrentThread();
  void assertInLoopThread();
  void quit();
  void updateChannel(Channel *channel);
  void queueInLoop(const Functor &cb);
  void runInLoop(const Functor &cb);  //作用？
 private:
  typedef std::vector<Channel *> ChannelList;

  std::vector<Functor> pendingFunctors;
  std::atomic<bool> callingPendingFunctors_;
  std::atomic<bool> looping_;
  std::mutex mutex_;
  const pthread_t threadId_;
  bool quit_;
  ChannelList activeChannels_;
  std::shared_ptr<Poller> poller_;  // poller_所指在何处？？
  int wakeupFd_;
  std::shared_ptr<Channel> wakeupChannel_;

  void handleRead();
  void wakeup();
  void doPendingFunctors();
};
}  // namespace yy