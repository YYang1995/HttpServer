#include "../SocketOperation.h"
#include <iostream>
#include <arpa/inet.h>

using namespace std;
using namespace net;

int main()
{
  struct sockaddr_in addr;
  addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  addr.sin_port=4220;
  cout<<"init "<<addr.sin_addr.s_addr<<endl;
  cout<<SocketOperation::ipToString(addr)<<endl;
  cout<<SocketOperation::portToString(addr)<<endl;
}