#include "Socket.h"
#include "SocketOperation.h"

using namespace yy;
using namespace std;

Socket::Socket(int fd):sockfd_(fd) {

}

Socket::~Socket() {
  SocketOperation::close(sockfd_);
}

int Socket::getFd() {
  return sockfd_;
}

void Socket::bind(SocketAddr &addr) {
  SocketOperation::bind(sockfd_,addr.getAddrPtr());
}

void Socket::listen() {
  SocketOperation::listen(sockfd_);
}

int Socket::accept(SocketAddr &addr) {
//  SocketOperation::accept(sockfd_,addr.getAddrPtr());
  struct sockaddr_in temp;
  int ret=SocketOperation::accept(sockfd_,&temp);
  if(ret>0){
    addr.setAddr(temp);
  }
  return ret;
}

void Socket::setTcpNoDelay() {
  SocketOperation::setTcpNoDelay(sockfd_);
}

int Socket::shutDownWrite() {
  SocketOperation::shutdownWrite(sockfd_);
}

