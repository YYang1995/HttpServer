#pragma once
#include <netinet/in.h>
#include <string>

namespace net
{
class SocketAddr{
public:
  SocketAddr(uint16_t port=0);
  SocketAddr(struct sockaddr_in addr);
  SocketAddr(const std::string &addrPort);
  SocketAddr(const std::string &addr,uint16_t port);

  void setAddr(struct sockaddr_in addr);
  struct sockaddr_in getAddr();
  struct sockaddr_in* getAddrPtr();
  std::string ipToString();
  std::string portToString();
private:
  struct sockaddr_in sockaddr_;
};
}