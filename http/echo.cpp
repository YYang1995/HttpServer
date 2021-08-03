#include "echo.h"

#include <iostream>

using namespace yy;
using namespace std;

Echo::Echo(EventLoop *loop, SocketAddr &addr) :TcpServer(loop, addr) {}

Echo::~Echo() {}

void Echo::connectCallback(TcpConnect::ptr tcpConnect)
{
  cout << "new connect: " << tcpConnect->getAddr().toString() << "<count> "
       << getConnectCount() << endl;
}

void messageCallback(TcpConnect::ptr tcpConnect,Buffer &Buffer)
{
  cout<<"thread id:"<<std::this_thread::get_id()<<endl;
    string addr = tcpConnect->getAddr().toString();
    string data = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
    //buffer.readAllAsString(data);
    //cout<<"receive data form "<<addr<<":"<<data<<endl;
    //base::Log::OUT(base::Log::Info)<<"receive data form "<<addr<<":"<<data;
    //data+=" kick back!";
    tcpConnect->write(data);
}

void writeCompleteCallback(yy::TcpConnect::ptr tcpConnect) 
{
    cout<<"thread id:"<<std::this_thread::get_id()<<endl;
    string addr = tcpConnect->getAddr().toString();
    cout<<addr<<":"<<"write complet "<<endl;
}

void connectCloseCallback(yy::TcpConnect::ptr tcpConnect) 
{
    string addr = tcpConnect->getAddr().toString();
    cout<<"close connect :"<<addr<<endl;
}