#pragma once
#include <functional>
#include <memory>

#include "../base/noncopyable.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"

namespace yy {
class TcpAcceptor : noncopyable {
public:
  typedef std::shared_ptr<TcpAcceptor> ptr;
  typedef std::function<void(int sockfd,  SocketAddr &)> NewConnectCallback;

  TcpAcceptor(EventLoop *loop, SocketAddr &addr);
  ~TcpAcceptor();
  void listen();
  bool isListen();
  void setNewConnectCallback(const NewConnectCallback &callback);

private:
  EventLoop *loop_;
  std::shared_ptr<Socket> socket_;
  std::shared_ptr<Channel> event_;
  bool listening_;
  NewConnectCallback newConnectCallback_;
  void acceptHandle();
};
}// namespace yy