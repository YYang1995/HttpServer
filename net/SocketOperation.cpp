#include "SocketOperation.h"

#include <netinet/tcp.h>  //for tcp_nodelay
#include <string.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "../base/ALog.h"

using namespace std;
using namespace net;
using namespace base;

const uint32_t SocketOperation::Ipv4AddrAny = htonl(INADDR_ANY);

int SocketOperation::createNonblockingSocket()
{
  int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                        IPPROTO_TCP);
  if (sockfd < 0)
  {
    std::cerr << "create non-block socket error" << std::endl;
  }
  return sockfd;
}

int SocketOperation::bind(int sockfd, const struct sockaddr_in *addr)
{
  int ret = ::bind(sockfd, (struct sockaddr *)(addr), sizeof(struct sockaddr));
  if (ret < 0)
  {
    // std::cerr << "bind socket error" << std::endl;
    LOG_FATAL("bind socket error");
  }
  return ret;
}

int SocketOperation::listen(int sockfd)
{
  int ret = ::listen(sockfd, SOMAXCONN);
  if (ret < 0)
  {
    // std::cerr << "listen socket error" << std::endl;
    LOG_FATAL("listen socket error");
  }
  return ret;
}

int SocketOperation::connect(int sockfd, const struct sockaddr *addr)
{
  int ret = ::connect(sockfd, addr,
                      static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
  if (ret < 0)
  {
    // std::cerr << "connect error" << std::endl;
    LOG_FATAL("connect error");
  }
  return ret;
}

int SocketOperation::accept(int sockfd, struct sockaddr_in *addr)
{
  socklen_t addrlen = sizeof(struct sockaddr_in);
  // int ret = ::accept(sockfd, (struct sockaddr *)addr, &addrlen);
  int ret = ::accept4(sockfd, (struct sockaddr *)addr, &addrlen,
                      SOCK_CLOEXEC | SOCK_NONBLOCK);
  if (ret < 0)
  {
    LOG_ERROR("accept socket error. Error message= %s",strerror(errno));
  }
  return ret;
}

ssize_t SocketOperation::read(int sockfd, void *buf, size_t count)
{
  return ::read(sockfd, buf, count);
}

ssize_t SocketOperation::readv(int sockfd, const struct iovec *iov, int iovcnt)
{
  return ::readv(sockfd, iov, iovcnt);
}

ssize_t SocketOperation::write(int sockfd, const void *buf, size_t count)
{
  return ::write(sockfd, buf, count);
}

void SocketOperation::close(int sockfd)
{
  if (::close(sockfd))
  {
    // std::cerr << "close sockfd error" << std::endl;
    LOG_ERROR("close sockfd error");
  }
}

int SocketOperation::shutdownWrite(int sockfd)
{
  int ret = ::shutdown(sockfd, SHUT_WR);
  if (ret < 0)
  {
    // std::cerr << "shutdown sockfd error" << std::endl;
    LOG_ERROR("shutdownWrite error");
  }
  return ret;
}

void SocketOperation::setTcpNoDelay(int sockfd)
{
  int opt = 1;
  ::setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
}

//使addr的端口为port，接受ipv4为任意
void SocketOperation::getAddrAnyIpv4(struct sockaddr_in &addr, uint16_t port)
{
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = Ipv4AddrAny;
}
/**
 * 将addr的地址设为addtstr，端口设置为port
 * @param addrstr ipv4地址
 * @param port 端口
 * @param addr 将被修改的socketaddr_in
 * @return success返回true
 */
bool SocketOperation::toAddrIpv4(const std::string &addrstr, uint16_t port,
                                 struct sockaddr_in &addr)
{
  //可直接调用inet_addr
  std::vector<int> ip;
  size_t first = 0;
  while (true)
  {
    auto last = addrstr.find('.', first);
    if (last == addrstr.npos)
    {
      ip.push_back(std::stoi(addrstr.substr(first, addrstr.size() - first)));
      break;
    }
    ip.push_back(std::stoi(addrstr.substr(first, last - first)));
    first = last + 1;
  }
  if (ip.size() != 4) return false;
  uint32_t addr32 = 0;
  for (auto i : ip)
  {
    if (i < 0 || i > 255)
    {
      return false;
    }
    addr32 <<= 8;
    addr32 |= i;
  }
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = addr32;
  return true;
}

bool SocketOperation::toAddrIpv4(const std::string &addrstr,
                                 struct sockaddr_in &addr)
{
  auto pos = addrstr.find(':');
  if (pos == addrstr.npos)
  {
    return false;
  }
  return toAddrIpv4(addrstr.substr(0, pos), std::stoi(addrstr.substr(pos + 1)),
                    addr);
}

//点分十进制ip:port转为字符串,accept接收到网络序，这里转为主机序   
string SocketOperation::ipToString(struct sockaddr_in addr)
{
  string ip;
  uint8_t *addrArray = (uint8_t *)&addr.sin_addr.s_addr;
  for (int i = 0; i <= 3; i++)
  {
    ip.append(std::to_string((int)(addrArray[i])));
    if (i != 3)
    {
      ip.push_back('.');
    }
  }
  return ip;
}

string SocketOperation::portToString(struct sockaddr_in addr)
{
  int port = (int)addr.sin_port;
  return std::to_string(port);
}