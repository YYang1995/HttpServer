#include <iostream>

#include "../../net/EventLoop.cpp"
#include "../../net/EventLoop.h"
#include "../../net/TcpServer.h"

using namespace std;
using namespace yy;

void connectCallback(TcpConnect::ptr tcpConnect)
{
  cout << "new connection arrived!It's name is  " << tcpConnect->getName()
       << endl;
}
void messageCallback(TcpConnect::ptr tcpConnect, Buffer &buffer) 
{
  cout << "Echo messageCallback\n";
}
void writeCompleteCallback(TcpConnect::ptr tcpConnect) {}
void connectCloseCallback(TcpConnect::ptr tcpConnect)
{
  cout << "connectint close\n";
}
class Echo2
{
 public:
  Echo2(EventLoop *loop, SocketAddr &addr) : server(loop, addr)
  {
    server.setConnnectCallback(std::bind(&connectCallback,std::placeholders::_1));
    server.setMessageCallback(std::bind(&messageCallback,std::placeholders::_1,std::placeholders::_2));
  };
  ~Echo2() = default;
  void start()
  {
    server.start();
  }
 private:
  TcpServer server;
};

int main()
{
  EventLoop loop;
  SocketAddr addr(4220);

  Echo2 echo(&loop, addr);
  echo.start();
  loop.loop();
}