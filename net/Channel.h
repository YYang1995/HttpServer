#pragma once
#include <functional>

namespace net
{
class EventLoop;

class Channel
{
 public:
  typedef std::function<void()> EventCallback;
  Channel(EventLoop *loop, int fd);
  ~Channel();
  void handleEvent();

  void setReadCallback(const EventCallback &cb) { readCallback_ = cb; }
  void setWriteCallback(const EventCallback &cb) { writeCallback_ = cb; }
  void setErrorCallback(const EventCallback &cb) { errorCallback_ = cb; }
  void setCloseCallback(const EventCallback &cb) { closeCallback_ = cb; }

  int fd() const { return fd_; }
  int events() const { return events_; }
  void set_revents(int revt) { revents_ = revt; }
  bool isNoneEvent() const { return events_ == kNoneEvent; }

  void enableReading()
  {
    events_ |= kReadEvent;
    update();
  }
  void enableWriting()
  {
    events_ |= kWriteEvent;
    update();
  }
  void disableWritinkg()
  {
    events_ &= ~kWriteEvent;
    update();
  }
  void disableAll()
  {
    events_ = kNoneEvent;
    update();
  }
  bool isWriting() { return events_ & kWriteEvent; }
  int index() { return index_; }
  void set_index(int index) { index_ = index; }
  void remove();

  EventLoop *ownerLoop() { return loop_; }

 private:
  void update();
  static const int kNoneEvent;
  static const int kReadEvent;
  static const int kWriteEvent;

  EventLoop *loop_;
  const int fd_;
  int events_;   //关心的事件
  int revents_;  //发生的事件
  int index_;    // for poller
  bool eventHandling_;  

  EventCallback readCallback_;
  EventCallback writeCallback_;
  EventCallback errorCallback_;
  EventCallback closeCallback_;
};
}  // namespace net