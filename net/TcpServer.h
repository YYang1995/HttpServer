#pragma once
#include <map>
#include <memory>
#include <string>

#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "SocketAddr.h"
#include "TcpAcceptor.h"
#include "TcpConnect.h"

namespace yy
{
class TcpServer
{
 public:

  TcpServer(EventLoop *loop, SocketAddr &addr);
  virtual ~TcpServer();
  void start();
  //三个半事件
  // virtual void connectCallback(TcpConnect::ptr tcpConnect) = 0;
  // virtual void messageCallback(TcpConnect::ptr tcpConnect, Buffer &buffer) = 0;
  // virtual void writeCompleteCallback(TcpConnect::ptr tcpConnect) = 0;
  // virtual void connectCloseCallback(TcpConnect::ptr tcpConnect) = 0;

  void addConnect(std::string name, TcpConnect::ptr connect);
  void addConnect(std::string name, TcpConnect *connect);

  void setConnnectCallback(const ConnectionCallback &cb)
  {
    connectionCallback_=cb;
  }
  void setMessageCallback(const MessageCallback &cb)
  {
    messageCallback_=cb;
  }
  void setWriteCompleteCallback(const WriteCompleteCallback &cb)
  {
    writeCompleteCallback_=cb;
  }

  bool havaConnect(std::string name);
  void removeConnect(const std::shared_ptr<TcpConnect> &conn);  //必须是const
  long getConnectCount() const;
  void removeConnectionInLoop(const std::shared_ptr<TcpConnect> &conn);

 private:
  EventLoop *loop_;
  SocketAddr tcpAddr_;
  TcpAcceptor::ptr tcpAccpet_;
  std::map<std::string, TcpConnect::ptr> connectPool_;

  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCompleteCallback_;

  void newConnected(int sockfd, SocketAddr &addr);
  void connectCloseEvent(TcpConnect::ptr connect);
  std::atomic<bool> isStart_;
  std::shared_ptr<EventLoopThreadPool> threadPool_;
  int nextId;  //用于连接name的唯一性
};
}  // namespace yy