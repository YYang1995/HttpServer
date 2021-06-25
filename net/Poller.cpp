#include "Poller.h"

#include <assert.h>
#include <string.h>
#include <unistd.h>

#include <iostream>


namespace yy {
Poller::Poller(EventLoop *loop) : ownerLoop_(loop) {
}
Poller::~Poller() {
}

void Poller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const {
  for (auto pfd = pollfds_.begin(); pfd != pollfds_.end() && numEvents > 0; pfd++) {
    numEvents--;
    auto ch = channels_.find(pfd->fd);
    assert(ch != channels_.end());
    Channel *channel = ch->second;
    assert(channel->fd() == pfd->fd);
    channel->set_revents(pfd->events);
    activeChannels->push_back(channel);
  }
}

void Poller::poll(int timeoutMs, ChannelList *activeChannels) {
  int numEvents = ::poll(pollfds_.data(), pollfds_.size(), timeoutMs);
  if (numEvents > 0) {
    std::cout << numEvents << " events happened!\n";
    fillActiveChannels(numEvents, activeChannels);
  } else if (numEvents == 0) {
//    std::cout << "nothing happened\n";
  } else {
    std::cerr << "Poller::poll()\n";
  }
}

void Poller::updateChannel(Channel *channel) {
  assertInLoopThread();
  std::cout << "fd = " << channel->fd() << " events= " << channel->events() << std::endl;
  if (channel->index() < 0) {
    assert(channels_.find(channel->fd()) == channels_.end());
    struct pollfd pfd {};
    pfd.fd = channel->fd();
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    pollfds_.push_back(pfd);
    int idx = static_cast<int>(pollfds_.size()) - 1;
    channel->set_index(idx);
    channels_[pfd.fd] = channel;

  } else {
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    int idx = channel->index();
    assert(idx >= 0 && idx < static_cast<int>(pollfds_.size()));
    struct pollfd &pfd = pollfds_[idx];
    assert(pfd.fd == channel->fd() || pfd.fd == -1);
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    if (channel->isNoneEvent()) {
      pfd.fd = -1;
    }
  }
}

void EventLoop::queueInLoop(const Functor &cb)
{
  {
    std::lock_guard<std::mutex> lock(mutex_);
    pendingFunctors.push_back(cb);
  }
  if(!isInLoopThread() || callingPendingFunctors_)
  {
    wakeup();
  }
}
}// namespace yy
