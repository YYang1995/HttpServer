#include "Epoll.h"

#include <assert.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>

#include "../base/ALog.h"
using namespace base;
using namespace std;
using namespace net;

namespace
{
const int kNew = -1;
const int kAdd = 1;
const int kDelete = 2;
}  // namespace

Epoll::Epoll(EventLoop *loop) : loop_(loop), epfd_(epoll_create(5)), events_(16)
{
  if (epfd_ < 0)
  {
    // cerr << "Epoll::Epoll() error!" << endl;
    LOG_FATAL("Epoll::Epoll() error!");
  }
}

Epoll::~Epoll() { ::close(epfd_); }

void Epoll::updateChannel(Channel *channel)
{
  int index = channel->index();
  if (index == kNew || index == kDelete)
  {
    int fd = channel->fd();
    if (index == kNew)
    {
      assert(channels_.find(fd) == channels_.end());
      channels_[fd] = channel;
    }
    else
    {
      //TODO
      assert(channels_.find(fd) != channels_.end());
      assert(channels_[fd] == channel);
    }
    channel->set_index(kAdd);
    update(EPOLL_CTL_ADD, channel);
  }
  else
  {
    int fd = channel->fd();
    assert(channels_.find(fd) != channels_.end());
    assert(channels_[fd] == channel);
    assert(index = kAdd);
    if (channel->isNoneEvent())
    {
      update(EPOLL_CTL_DEL, channel);
      channel->set_index(kDelete);
    }
    else
    {
      update(EPOLL_CTL_MOD, channel);
    }
  }
}

void Epoll::update(int operation, Channel *channel)
{
  epoll_event event;
  memset(&event, 0, sizeof event);
  event.data.fd = channel->fd();
  event.events = channel->events();
  event.data.ptr = channel;  //这里设置ptr指向channel
  int fd = channel->fd();
  if (epoll_ctl(epfd_, operation, fd, &event) < 0)
  {
    // cerr << "epoll_ctl error\n";
    LOG_ERROR("epoll_ctl error. %s",strerror(errno));
    return;
  }
}

void Epoll::fillActiveChannels(int numEvents, ChannelList *channelList)
{
  for (int i = 0; i < numEvents; i++)
  {
    Channel *channel = static_cast<Channel *>(
        events_[i].data.ptr);  // 在Epoll::update中设置妥了
    int fd = channel->fd();
    const auto iter = channels_.find(fd);
    if (iter == channels_.end() || iter->second != channel)
    {
      // cerr << "Epoll::fillActiveChannels error\n";
      LOG_ERROR("Epoll::fillActiveChannels error");
      return;
    }

    channel->set_revents(events_[i].events);
    channelList->push_back(channel);
  }
}

void Epoll::poll(int timeoutMs, ChannelList *activeChannels)
{
  int numEvents = epoll_wait(epfd_, &(*events_.begin()),
                             static_cast<int>(events_.size()), timeoutMs);
  if (numEvents > 0)
  {
    fillActiveChannels(numEvents, activeChannels);
  }
  else if (numEvents == 0)
  {
    // nothing happened
  }
  else
  {
    if (errno != EINTR)
    {
      // cerr << "Epoll::poll().errno=" << errno << endl;
      LOG_ERROR("Epoll::poll().errno= %d",errno);
    }
  }
}

void Epoll::removeChannel(Channel *channel)
{
  int fd = channel->fd();
  assert(channels_.find(fd) != channels_.end());
  assert(channels_[fd] == channel);
  assert(channel->isNoneEvent());
  int index = channel->index();
  assert(index == kAdd || index == kDelete);
  auto n = channels_.erase(fd);
  assert(n == 1);
  if (index == kAdd)
  {
    update(EPOLL_CTL_DEL, channel);
  }
  channel->set_index(kNew);
}

