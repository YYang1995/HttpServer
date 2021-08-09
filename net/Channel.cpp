#include "Channel.h"

#include <sys/epoll.h>
#include <sys/poll.h>

#include <iostream>

#include "EventLoop.h"

using namespace std;
using namespace yy;

namespace yy
{
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN ; //| POLLPRI | POLLRDHUP
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1)
{
}

void Channel::update() { loop_->updateChannel(this); }

void Channel::handleEvent()
{
  cout << "Channel::handleEvent() fd= "<<fd_<<endl;
  if (revents_ & POLLNVAL)
  {
    std::cerr << "Channel::handleEvent() POLLNAVAL;" << std::endl;
  }
  if (revents_ & (POLLERR | POLLNVAL))
  {
    if (errorCallback_) errorCallback_();
  }
  if (revents_ & (POLLIN | POLLPRI))
  {
    if (readCallback_) readCallback_();
  }
  if (revents_ & (POLLOUT))
  {
    if (writeCallback_) writeCallback_();
  }
  if(revents_ & EPOLLRDHUP && !(revents_ & EPOLLIN))
  {
    cout<<"herr?\n";
    if(closeCallback_) closeCallback_();
  }
}
}  // namespace yy