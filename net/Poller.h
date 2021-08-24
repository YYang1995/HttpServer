#pragma once
#include <poll.h>

#include <iostream>
#include <map>
#include <vector>

#include "Channel.h"
#include "EventLoop.h"

namespace net
{
class EventLoop;

class Poller
{
 public:
  typedef std::vector<Channel *> ChannelList;
  Poller(EventLoop *loop);
  virtual ~Poller();

  void updateChannel(Channel *channel);
  void poll(int timeoutMs, ChannelList *activeChannels);

 private:
  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;

  typedef std::map<int, Channel *> ChannelMap;
  typedef std::vector<pollfd> PollFdList;
  ChannelMap channels_;
  PollFdList pollfds_;

  EventLoop *ownerLoop_;
};
}  // namespace net