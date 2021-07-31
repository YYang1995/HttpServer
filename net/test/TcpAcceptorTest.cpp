#include <unistd.h>
#include <string.h>

#include <iostream>

#include "../TcpAcceptor.h"

using namespace yy;
using namespace std;


void newConnection(int sockfd, SocketAddr& socketAddr) {
  char msg[]="how are you";
  cout << "new conection from " << socketAddr. toString()<< endl;
  ::write(sockfd,msg,strlen(msg));
  ::close(sockfd);
}
int main() {
  cout << "main " << getpid();
  SocketAddr listenAddr(9981);
  EventLoop loop;
  TcpAcceptor acceptor(&loop, listenAddr);
  acceptor.setNewConnectCallback(newConnection);
  acceptor.listen();

  loop.loop();
}