#pragma once
#include <map>
#include <memory>
#include <string>

#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "SocketAddr.h"
#include "TcpAcceptor.h"
#include "TcpConnect.h"

namespace net
{
class TcpServer
{
 public:
  TcpServer(EventLoop *loop, SocketAddr &addr);
  ~TcpServer();
  void start();

  void addConnect(std::string name, TcpConnect::ptr connect);
  void addConnect(std::string name, TcpConnect *connect);

  void setConnnectCallback(const ConnectionCallback &cb)
  {
    connectionCallback_ = cb;
  }
  void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
  void setWriteCompleteCallback(const WriteCompleteCallback &cb)
  {
    writeCompleteCallback_ = cb;
  }
  // TcpConection::closeCallback绑定到这
  void removeConnect(const std::shared_ptr<TcpConnect> &conn);  

  bool havaConnect(std::string name);
  long getConnectCount() const;
  void removeConnectionInLoop(const std::shared_ptr<TcpConnect> &conn);

 private:
  EventLoop *mainloop_;
  SocketAddr tcpAddr_;
  TcpAcceptor::ptr tcpAccpet_;
  std::map<std::string, TcpConnect::ptr> connectPool_;

  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCompleteCallback_;

  void newConnected(int sockfd, SocketAddr &addr);
  std::atomic<bool> isStart_;
  std::unique_ptr<EventLoopThreadPool> threadPool_;
  int nextId;  //用于name的唯一性

  std::mutex mtx_;
  
};
}  // namespace net