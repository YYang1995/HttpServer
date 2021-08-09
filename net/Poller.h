#pragma once
#include <poll.h>

#include <iostream>
#include <map>
#include <vector>

#include "../base/noncopyable.h"
#include "Channel.h"
#include "EventLoop.h"

namespace yy
{
class EventLoop;

class Poller : public noncopyable
{
 public:
  typedef std::vector<Channel *> ChannelList;
  Poller(EventLoop *loop);
  virtual ~Poller();

  void updateChannel(Channel *channel);
  // void assertInLoopThread() {
  //   //    ownerLoop_->assertInLoopThread();
  //   std::cout << "assertInLoopThread\n";
  // }
  // TODO muduo这里返回自己实现的Timestamp
  void poll(int timeoutMs, ChannelList *activeChannels);

 private:
  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;

  typedef std::map<int, Channel *> ChannelMap;
  typedef std::vector<pollfd> PollFdList;
  ChannelMap channels_;
  PollFdList pollfds_;

  EventLoop *ownerLoop_;
};
}  // namespace yy