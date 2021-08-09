#include <fcntl.h>

#include <iostream>

#include "../Socket.h"
#include "../SocketOperation.h"

using namespace std;
using namespace yy;

int main()
{
  Socket serverSocket(SocketOperation::createNonblockingSocket());
  SocketAddr socketAddr(4220);
  serverSocket.bind(socketAddr);
  serverSocket.listen();
  SocketAddr clientSocket;
  //由于是非阻塞的，所以用while(ture)；accept确实可用
  while (1)
  {
    auto ret = serverSocket.accept(clientSocket);
    if (ret > 0)
    {
      cout << "ok\n";
      break;
    }
  }
}