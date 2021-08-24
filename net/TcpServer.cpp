#include "TcpServer.h"

#include <assert.h>

#include <iostream>

#include "../base/ALog.h"
using namespace base;
using namespace std;
using namespace net;

TcpServer::TcpServer(EventLoop *loop, SocketAddr &addr)
    : mainloop_(loop),
      tcpAddr_(addr),
      tcpAccpet_(new TcpAcceptor(mainloop_, addr)),
      isStart_(false),
      threadPool_(new EventLoopThreadPool(loop)),
      nextId(1),
      mtx_()
{
  tcpAccpet_->setNewConnectCallback(std::bind(&TcpServer::newConnected, this,
                                              std::placeholders::_1,
                                              std::placeholders::_2));
}

TcpServer::~TcpServer() {}

void TcpServer::start()
{
  // threadPool_->init();
  mainloop_->runInLoop(std::bind(&TcpAcceptor::listen, tcpAccpet_.get()));
  isStart_ = true;
}

void TcpServer::newConnected(int sockfd, SocketAddr &addr)
{
  EventLoop *ioLoop = threadPool_->getOneLoopFromPool();
  TcpConnect::ptr tcpConnect(new TcpConnect(ioLoop, addr, sockfd));
  string connName = addr.ipToString() + ":" + addr.portToString() + "_" +
                    std::to_string(nextId);
  tcpConnect->setName(connName);
  addConnect(connName, tcpConnect);
  nextId++;
  tcpConnect->setConnectionCallback(connectionCallback_);
  tcpConnect->setMessageCallback(messageCallback_);
  tcpConnect->setWriteCompleteCallback(writeCompleteCallback_);
  tcpConnect->setCloseCallback(
      std::bind(&TcpServer::removeConnect, this, std::placeholders::_1));
  ioLoop->runInLoop(std::bind(&TcpConnect::connectEstablished, tcpConnect));
  LOG_INFO("new connect [ip:port]= %s. Total count= %d", connName.c_str(),
           getConnectCount());
}

long TcpServer::getConnectCount() const { return connectPool_.size(); }

void TcpServer::addConnect(string name, TcpConnect::ptr connect)
{
  connectPool_.insert(std::pair<string, TcpConnect::ptr>(name, connect));
}

void TcpServer::addConnect(string name, TcpConnect *connect)
{
  TcpConnect::ptr sp(connect);
  addConnect(name, sp);
}

bool TcpServer::havaConnect(std::string name)
{
  return connectPool_.count(name);
}

void TcpServer::removeConnect(const shared_ptr<TcpConnect> &conn)
{
  mainloop_->queueInLoop(
      std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const shared_ptr<TcpConnect> &conn)
{
  mainloop_->assertInLoopThread();
  nextId--;
  size_t n;
  {
    std::lock_guard<std::mutex> lock(mtx_);
    n = connectPool_.erase(conn->getName());  //是否需要加锁

  }
  if (n != 1)
  {
    LOG_ERROR("n=%d,pool totol size= %d", n, connectPool_.size());
  }
  (void)n;
  assert(n==1);
  EventLoop *ioLoop = conn->getLoop();
  ioLoop->runInLoop(std::bind(&TcpConnect::connectDestroyed, conn));
}
