#pragma once
#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "Channel.h"
#include "Epoll.h"

namespace net
{
class Channel;
// class Poller;
class Epoll;
class EventLoop
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
  void removeChannel(Channel *Channel);
  void queueInLoop(Functor cb);
  void runInLoop(Functor cb); 
 private:
  typedef std::vector<Channel *> ChannelList;

  std::vector<Functor> pendingFunctors;
  std::atomic<bool> callingPendingFunctors_;
  std::atomic<bool> looping_;
  std::mutex mutex_;
  const pthread_t threadId_;
  bool quit_;
  ChannelList activeChannels_;
  std::unique_ptr<Epoll> poller_;
  int wakeupFd_;
  std::unique_ptr<Channel> wakeupChannel_;  
  Channel *currentActiveChannel_;
  void handleWakeupRead();
  void wakeup();
  void doPendingFunctors();
};
}  // namespace net