#include "../SocketOperation.h"
#include <iostream>
#include <arpa/inet.h>

using namespace std;
using namespace yy;

int main()
{
  struct sockaddr_in addr;
  addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  cout<<SocketOperation::ipToString(addr)<<endl;
}