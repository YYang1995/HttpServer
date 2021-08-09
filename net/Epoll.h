#pragma once
#include "Channel.h"
#include "EventLoop.h"
#include <map>
#include <vector>
#include <sys/epoll.h>

namespace yy
{
class EventLoop;
class Epoll
{
 public:
  using ChannelList=std::vector<Channel*>;
  Epoll(EventLoop *loop);
  ~Epoll();

  bool updateChannel(Channel *Channel);
  void poll(int timeoutMs,ChannelList *activeChannels);

 private:
  using ChannnelMap = std::map<int, Channel *>;
  using EpollFdList = std::vector<Channel *>;

  EventLoop *loop_;
  ChannnelMap channels_;
  ChannelList activeChannels_;
  std::vector<epoll_event> events_;
  int epfd_;
  // EpollFdList 
  void fillActiveChannels(int numEvents,ChannelList *channelList);
  bool update(int operation,Channel *Channel);
};
}  // namespace yy