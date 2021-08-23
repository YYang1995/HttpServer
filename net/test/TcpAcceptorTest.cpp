#include <unistd.h>

#include <iostream>

#include "../../base/ALog.h"
#include "../EventLoop.cpp"
#include "../TcpAcceptor.cpp"
#include "../TcpAcceptor.h"

using namespace std;
using namespace net;

void newConnect(int fd, SocketAddr &addr)
{
  cout << "new connect !It's Ip is " << addr.ipToString().c_str() << endl;
}
int main()
{
  ALog::init(nullptr, false);
  EventLoop loop;
  SocketAddr addr(4220);
  TcpAcceptor acceptor(&loop, addr);
  acceptor.setNewConnectCallback(newConnect);

  acceptor.listen();  
  loop.loop();
  ALog::shutdown();
}