#pragma once
#include "Channel.h"
#include "EventLoop.h"
#include <map>
#include <vector>
#include <sys/epoll.h>

namespace net
{
class EventLoop;
class Epoll
{
 public:
  using ChannelList=std::vector<Channel*>;
  Epoll(EventLoop *loop);
  ~Epoll();

  void updateChannel(Channel *Channel);
  void removeChannel(Channel *channel);
  void poll(int timeoutMs,ChannelList *activeChannels);

 private:
  using ChannnelMap = std::map<int, Channel *>;
  using EpollFdList = std::vector<Channel *>;

  EventLoop *loop_;
  ChannnelMap channels_;
  ChannelList activeChannels_;
  std::vector<epoll_event> events_;
  int epfd_;
  void fillActiveChannels(int numEvents,ChannelList *channelList);
  void update(int operation,Channel *Channel);
};
}  // namespace net