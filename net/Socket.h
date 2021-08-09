#pragma once
#include <sys/socket.h>
#include "SocketAddr.h"


namespace yy
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
private:
  int sockfd_;
};
}