#pragma once
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "SocketAddr.h"
#include "TcpAcceptor.h"
#include "TcpConnect.h"
#include <map>
#include <memory>
#include <string>

namespace yy {
class TcpServer {
public:
  TcpServer(EventLoop *loop, SocketAddr &addr);
  virtual ~TcpServer();
  void start();
  //三个半事件
  virtual void connectCallback(TcpConnect::ptr tcpConnect) = 0;
  virtual void messageCallback(TcpConnect::ptr tcpConnect, Buffer &buffer) = 0;
  virtual void writeCompleteCallback(TcpConnect::ptr TcpConnect) = 0;
  virtual void connectCloseCallback(TcpConnect::ptr TcpConnect) = 0;

  void addConnect(std::string name, TcpConnect::ptr connect);
  void addConnect(std::string name, TcpConnect *connect);

  bool havaConnect(std::string name);
  void removeConnect(std::string name);
  long getConnectCount() const;

private:
  EventLoop *loop_;
  SocketAddr tcpAddr_;
  TcpAcceptor::ptr tcpAccpet_;
  std::map<std::string, TcpConnect::ptr> connectPool_;

  void newConnected(int sockfd, SocketAddr &addr);
  void connectCloseEvent(TcpConnect::ptr connect);
  std::atomic<bool> isStart_;
  std::shared_ptr<EventLoopThreadPool> threadPool_;
};
} // namespace yy