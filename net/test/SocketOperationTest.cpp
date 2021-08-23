#include "../SocketOperation.h"
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;
using namespace net;

int main()
{
  struct sockaddr_in addr;
  addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //返回大端
  addr.sin_port=4220;
  cout<<"主机序： "<<ntohl(addr.sin_addr.s_addr)<<endl;
  cout<<"网络序： "<<addr.sin_addr.s_addr<<endl;
  cout<<SocketOperation::ipToString(addr)<<endl;
  cout<<SocketOperation::portToString(addr)<<endl;
} 