#include "TcpServer.h"
#include <assert.h>
#include <iostream>

using namespace std;
using namespace yy;

TcpServer::TcpServer(EventLoop *loop, SocketAddr &addr)
    : loop_(loop),
      tcpAddr_(addr),
      tcpAccpet_(new TcpAcceptor(loop, addr)),
      isStart_(false),
      threadPool_(new EventLoopThreadPool(loop))
{
  tcpAccpet_->setNewConnectCallback(std::bind(&TcpServer::newConnected, this,
                                              std::placeholders::_1,
                                              std::placeholders::_2));
}

TcpServer::~TcpServer() {}

void TcpServer::start()
{
  // threadPool_->init();
  // tcpAccpet_->listen();
  loop_->runInLoop(std::bind(&TcpAcceptor::listen,tcpAccpet_.get()));
  isStart_ = true;
}

void TcpServer::newConnected(int sockfd, SocketAddr &addr)
{

  EventLoop *ioLoop = threadPool_->getOneLoopFromPool();
  TcpConnect::ptr tcpConnect(new TcpConnect(ioLoop, addr, sockfd));
  addConnect(addr.toString(), tcpConnect);
  tcpConnect->setConnectionCallback(connectionCallback_);
  tcpConnect->setMessageCallback(messageCallback_);
  tcpConnect->setWriteCompleteCallback(writeCompleteCallback_);
  tcpConnect->setCloseCallback(std::bind(&TcpServer::removeConnect,this,std::placeholders::_1));
  ioLoop->runInLoop(std::bind(&TcpConnect::connectEstablished,tcpConnect));
    std::cout << "new connect addr " << tcpAddr_.toString()
            << " cnt: " << std::to_string(getConnectCount())<<endl;
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
  auto n=connectPool_.erase(conn->getName());
  assert(n==1);
  loop_->queueInLoop(std::bind(&TcpServer::removeConnectionInLoop,this,conn));
}

void TcpServer::removeConnectionInLoop(const shared_ptr<TcpConnect> &conn)
{
  EventLoop *ioLoop=conn->getLoop();
  ioLoop->runInLoop(std::bind(&TcpConnect::connectDestroyed,conn));
}

void TcpServer::connectCloseEvent(TcpConnect::ptr connect)
{
  // connectCloseCallback(connect);
  // removeConnect(connect->getName());
}
