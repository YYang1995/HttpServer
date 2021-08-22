#pragma once
#include <sys/socket.h>
#include "SocketAddr.h"


namespace net
{
class Socket
{
public:
  Socket(int fd);
  ~Socket();
  int getFd();
  void bind(SocketAddr &addr);
  void listen();
  int accept(SocketAddr &addr);
  void setTcpNoDelay();
  void setReusePort(bool on);
  int shutDownWrite();
  void setKeepAlive(bool on);
private:
  int sockfd_;
};
}