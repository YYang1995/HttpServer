#include "../TcpAcceptor.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace net;

int main()
{
  EventLoop loop;
  SocketAddr addr(4220);
  TcpAcceptor acceptor(&loop,addr);
  while(1)
  {
    sleep(1);
    acceptor.listen();
  }
}