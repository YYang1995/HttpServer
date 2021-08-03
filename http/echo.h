#pragma once

#include "../net/EventLoop.h"
#include "../net/TcpServer.h"

class Echo : public yy::TcpServer
{
 public:
  Echo(yy::EventLoop *loop, yy::SocketAddr &addr);
  ~Echo();
  virtual void connectCallback(yy::TcpConnect::ptr tcpConnect) override;
  virtual void messageCallback(yy::TcpConnect::ptr tcpConnect,
                               yy::Buffer &buffer) override;
  virtual void writeCompleteCallback(yy::TcpConnect::ptr TcpConnect) override;
  virtual void connectCloseCallback(yy::TcpConnect::ptr TcpConnect) override;
};
