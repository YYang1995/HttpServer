#include "Socket.h"

#include <assert.h>

#include <iostream>

#include "../base/ALog.h"
#include "SocketOperation.h"
#include "SocketOperation.cpp"


using namespace net;
using namespace base;
using namespace std;

Socket::Socket(int fd) : sockfd_(fd) {}

Socket::~Socket() { SocketOperation::close(sockfd_); }

int Socket::getFd() { return sockfd_; }

void Socket::bind(SocketAddr &addr)
{
  SocketOperation::bind(sockfd_, addr.getAddrPtr());
}

void Socket::listen() { SocketOperation::listen(sockfd_); }

int Socket::accept(SocketAddr &addr)
{
  struct sockaddr_in temp;
  int ret = SocketOperation::accept(sockfd_, &temp); //非阻塞
  if (ret > 0)
  {
    addr.setAddr(temp);
  }
  return ret;
}

void Socket::setTcpNoDelay() { SocketOperation::setTcpNoDelay(sockfd_); }

int Socket::shutDownWrite() { SocketOperation::shutdownWrite(sockfd_); }

void Socket::setReusePort(bool on)
{
  int optval = on ? 1 : 0;
  auto ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval,
                          static_cast<socklen_t>(sizeof optval));
  if (ret < 0)
  {
    // cerr<<"Socket::setReusePort(bool) error\n";
    LOG_ERROR("Socket::setReusePort(bool) error");
  }
}

void Socket::setKeepAlive(bool on)
{
  int optval = on ? 1 : 0;
  auto ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval,
                          static_cast<socklen_t>(sizeof optval));
  assert(ret == 0);
}