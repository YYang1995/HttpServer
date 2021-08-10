#pragma once
#include <memory.h>

#include <string>

#include "Buffer.h"
#include "EventLoop.h"
#include "Socket.h"

namespace yy
{
class TcpConnect;

typedef std::function<void(const std::shared_ptr<TcpConnect>&, Buffer &)>
    MessageCallback;
typedef std::function<void(const std::shared_ptr<TcpConnect>&)> WriteCompleteCallback;
typedef std::function<void(const std::shared_ptr<TcpConnect>&)> CloseCallback;
typedef std::function<void(const std::shared_ptr<TcpConnect>&)> ConnectionCallback;

class TcpConnect : public std::enable_shared_from_this<TcpConnect>
{
 public:
typedef std::shared_ptr<TcpConnect> ptr;
  enum ConnectState
  {
    Disconnected,
    Connecting,
    Connected,
    Disconnecting
  };

 public:
  TcpConnect(EventLoop *loop, SocketAddr &a, int fd);
  ~TcpConnect();

  void setMessageCallback(const MessageCallback &callback)
  {
    messageCallback_ = callback;
  };
  void setCloseCallback(const CloseCallback &callback)
  {
    closeCallback_ = callback;
  }
  void setWriteCompleteCallback(const WriteCompleteCallback &callback)
  {
    writeCompleteCallback_ = callback;
  };
  void setConnectionCallback(const ConnectionCallback &callback)
  {
    connectionCallback_=callback;
  }
  EventLoop *getLoop()
  {
    return loop;
  }
  SocketAddr &getAddr() { return addr; }
  const std::string getName() const { return name; }

  void setNoDelay();
  void shutDownWrite();

  void write(const char *data);
  void write(const std::string &data);
  void write(const void *data, uint32_t len);

  void connectEstablished();
  void connectDestroyed();
  void connectHandle();

 private:
  EventLoop *loop;
  SocketAddr addr;
  std::string name;
  std::unique_ptr<Socket> socket;
  std::unique_ptr<Channel> event;

  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  CloseCallback closeCallback_;
  WriteCompleteCallback writeCompleteCallback_;

  int state;

  Buffer readBuffer;
  Buffer writeBUffer;

  void readEvent();
  void closeEvent();
  void writeEvent();
  void errorEvent();
  void setState(int state) { this->state = state; }
};
}  // namespace yy