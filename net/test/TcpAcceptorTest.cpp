#include "../TcpAcceptor.h"
#include <iostream>
#include <unistd.h>

using namespace yy;
using namespace std;


void newConnection(int sockfd, SocketAddr& socketAddr)
{
   cout<<"new conection from "<<socketAddr.toString()<<endl;
   ::write(sockfd,"how are you?",13);
   ::close(sockfd);
}
int main()
{
  cout<<"main "<<getpid();
  SocketAddr listenAddr(9981);
  EventLoop loop;
  TcpAcceptor acceptor(&loop,listenAddr);
  acceptor.setNewConnectCallback(newConnection);
  acceptor.listen();

  loop.loop();
}