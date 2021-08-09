#include "../Socket.h"
#include <iostream>
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
  serverSocket.accept(clientSocket);

} 