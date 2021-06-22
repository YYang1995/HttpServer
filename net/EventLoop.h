#pragma once
#include "../base/noncopyable.h"
#include "Channel.h"
#include <atomic>
#include <vector>
#include <memory>
#include "Poller.h"


namespace yy {
class Channel;
class Poller;
class EventLoop : public noncopyable {
public:
  EventLoop();
  ~EventLoop();

  void loop();

  bool isInLoopThread();
  EventLoop *getEventLoopOfCurrentThread();
  void assertInLoopThread();
  void quit();
  void updateChannel(Channel *channel);
private:
  typedef std::vector<Channel*> ChannelList;

  std::atomic<bool> looping_;
  const pthread_t threadId_;
  bool quit_;
  ChannelList activeChannels_;
  std::shared_ptr<Poller> poller_;  //poller_所指在何处？？
};
}// namespace yy