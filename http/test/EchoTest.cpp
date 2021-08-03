#include "../echo.h"
#include "../../net/EventLoop.h"

using namespace std;
using namespace yy;

int main()
{
  EventLoop loop;
  SocketAddr addr(4220);
  Echo echoServer(&loop,addr);
  echoServer.start();
  loop.loop();

}