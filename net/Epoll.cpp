#include "Epoll.h"
#include <iostream>

#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

using namespace std;
using namespace yy;

namespace
{
const int kNew = -1;
const int kAdd = 1;
const int kDelete = 2;
}  // namespace

Epoll::Epoll(EventLoop *loop) : loop_(loop), epfd_(epoll_create(5)),events_(16)
{
  if (epfd_ < 0)
  {
    cerr << "Epoll::Epoll() error!" << endl;
  }
}

Epoll::~Epoll() { ::close(epfd_); }

bool Epoll::updateChannel(Channel *channel)
{
  int index = channel->index();
  int fd = channel->fd();
  if (index == kNew || index == kDelete)  //新事件或删除事件
  {
    if (index == kNew) //新事件
    {
      if (channels_.find(fd) != channels_.end())
      {
        cerr << "fd= " << fd << " must not exist in channels\n";
        return false;
      }
      channels_[fd] = channel;
    }
    else  //删除事件 ???
    {
      if(channels_.find(fd)==channels_.end())
      {
        cerr << "fd= " << fd << " must exist in channels\n";
        return false;
      }
      if(channels_[fd]!=channel)
      {
        cerr << "current channels does not match current. fd=" << fd << endl;
        return false;
      }
    }
    channel->set_index(kAdd);
    update(EPOLL_CTL_ADD, channel);
  }
  else
  {
    //更新已有事件
    if (channels_.find(fd) == channels_.end() || channels_[fd]!=channel || index!=kAdd)
    {
      cerr << "fd= " << fd << "must exist in channels\n";
      return false;
    }
    if(channel->isNoneEvent())
    {
      if(update(EPOLL_CTL_DEL,channel))
      {
        channel->set_index(kDelete);
        return true;
      }
    }
    else
    {
      return update(EPOLL_CTL_MOD,channel);
    }
  }
}

bool Epoll::update(int operation, Channel *channel)
{
  epoll_event event;
  memset(&event, 0, sizeof event);
  event.data.fd = channel->fd();
  event.events = channel->events();
  event.data.ptr = channel;  //这里设置ptr指向channel
  int fd = channel->fd();
  if (epoll_ctl(epfd_, operation, fd, &event) < 0)
  {
    cerr << "epoll_ctl error\n";
    return false;
  }
  return true;
}

void Epoll::fillActiveChannels(int numEvents, ChannelList *channelList)
{
  for (int i = 0; i < numEvents; i++)
  {
    Channel *channel =
        static_cast<Channel *>(events_[i].data.ptr);  // TODO 直接转换可行？
    int fd = channel->fd();
    auto iter = channels_.find(fd);
    if (iter == channels_.end() || iter->second != channel)
    {
      cerr << "Epoll::fillActiveChannels error\n";
      return;
    }
    channel->set_revents(events_[i].events);
    activeChannels_.push_back(channel);
  }
}

void Epoll::poll(int timeoutMs, ChannelList *activeChannels)
{
  int numEvents =
      epoll_wait(epfd_, &(*events_.begin()),static_cast<int>(events_.size()), timeoutMs);
  if (numEvents > 0)
  {
    fillActiveChannels(numEvents, &activeChannels_);
  }
  else if (numEvents == 0)
  {
    // nothing happened
  }
  else
  {
    if (errno != EINTR)
    {
      cerr << "Epoll::poll().errno=" <<errno<<endl;
    }
  }
}