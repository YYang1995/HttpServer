#include "TcpAcceptor.h"

#include <unistd.h>
#include "Socket.cpp"
#include <iostream>

#include "../base/ALog.h"
#include "SocketOperation.h"

using namespace net;
using namespace std;
using namespace base;

TcpAcceptor::TcpAcceptor(EventLoop *loop, SocketAddr &addr)
    : loop_(loop),
      socket_(new Socket(SocketOperation::createNonblockingSocket())),
      channel_(new Channel(loop, socket_->getFd())),
      listening_(false)
{
  socket_->setReusePort(true);
  socket_->bind(addr);
  channel_->setReadCallback(std::bind(&TcpAcceptor::acceptHandle, this));
  loop_->updateChannel(channel_.get());
}

TcpAcceptor::~TcpAcceptor()
{
  channel_->disableAll();
  channel_->remove();
}

void TcpAcceptor::listen()
{
  socket_->listen();
  listening_ = true;
  channel_->enableReading();
}

bool TcpAcceptor::isListen() { return listening_; }

void TcpAcceptor::setNewConnectCallback(const NewConnectCallback &callback)
{
  newConnectCallback_ = callback;
}

void TcpAcceptor::acceptHandle()
{
  SocketAddr connectAddr;
  int connectfd = -1;
  if ((connectfd = socket_->accept(connectAddr)) > 0)
  {
    LOG_INFO("new Connection! Its Ip is %s",connectAddr.ipToString().c_str());
    if (newConnectCallback_)
    {
      newConnectCallback_(connectfd, connectAddr);
    }
    else
    {
      ::close(connectfd);
    }
  }
}