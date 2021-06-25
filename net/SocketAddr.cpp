#include "SocketAddr.h"
#include "SocketOperation.h"

using namespace yy;
using namespace std;

SocketAddr::SocketAddr(uint16_t port){
  SocketOperation::getAddrAnyIpv4(sockaddr_,port);
}

SocketAddr::SocketAddr(struct sockaddr_in addr):sockaddr_(addr){

}

SocketAddr::SocketAddr(const std::string &addrPort):SocketAddr(std::stoi(addrPort)) {

}

/**
 * 将SocketAddr设置为下面的值
 * @param addr  ipv4 address
 * @param port  port
 */
SocketAddr::SocketAddr(const std::string &addr, uint16_t port) {
  SocketOperation::toAddrIpv4(addr,port,sockaddr_);
}

void SocketAddr::setAddr(struct sockaddr_in addr) {
  sockaddr_=addr;
}

struct sockaddr_in SocketAddr::getAddr() {
  return sockaddr_;
}

struct sockaddr_in* SocketAddr::getAddrPtr() {
  return &sockaddr_;
}

string SocketAddr::toString() {
  return SocketOperation::ipToString(sockaddr_);
}

