#include "../../net/EventLoop.h"
#include "../../net/EventLoop.cpp"
#include "../../net/TcpServer.h"
#include "../echo.h"
#include <iostream>

using namespace std;
using namespace yy;

class Echo2 : public TcpServer
{
 public:
  Echo2(EventLoop *loop,SocketAddr &addr):TcpServer(loop,addr){};
  ~Echo2()=default;
  virtual void connectCallback(TcpConnect::ptr tcpConnect) 
  {
    cout<<"new connection arrived!It's name is  "<<tcpConnect->getName()<<endl;
  }
  virtual void messageCallback(TcpConnect::ptr tcpConnect, Buffer &buffer) override
  {

  }
  virtual void writeCompleteCallback(TcpConnect::ptr tcpConnect){}
  virtual void connectCloseCallback(TcpConnect::ptr tcpConnect) {
    cout<<"connectint close\n";
  }

 private:

};

int main()
{
  EventLoop loop;
  SocketAddr addr(4220);
  
  Echo2 echo(&loop,addr);
  echo.start();
  loop.loop();
}