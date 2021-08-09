#include "TcpConnect.h"
#include <iostream>

using namespace yy;
using namespace std;

TcpConnect::TcpConnect(EventLoop *loop, SocketAddr &a, int fd)
    : loop(loop),
      addr(a),
      name(addr.toString()),
      event(new Channel(loop, fd)),
      socket(new Socket(fd)),
      state(Disconnected)
{
  setNoDelay();
  loop->updateChannel(event.get());
  event->setReadCallback(std::bind(&TcpConnect::readEvent, this));
  event->setWriteCallback(std::bind(&TcpConnect::writeEvent, this));
  event->setErrorCallback(std::bind(&TcpConnect::errorEvent, this));
  event->setCloseCallback(std::bind(&TcpConnect::closeCallback, this));
}

TcpConnect::~TcpConnect()
{
  event->disableAll();
  //  event->removeEvnet(shared_from_this()); TODO
}

void TcpConnect::setNoDelay() { socket->setTcpNoDelay(); }

void TcpConnect::shutDownWrite()
{
  if (state == Connected)
  {
    state = Disconnecting;
    socket->shutDownWrite();
  }
}

void TcpConnect::readEvent()
{
  int error = 0;
  int n = readBuffer.readFromIO(event->fd(), error);
  if (n > 0)
  {
    if (!!messageCallback)
    {
      messageCallback(shared_from_this(), readBuffer);
    }
  }
  else if (n == 0)
  {
    closeEvent();
  }
  else
  {
    std::cerr << "Error: TcpConnect read error" << std::to_string(error)
              << std::endl;
    closeEvent();
  }
}

void TcpConnect::closeEvent()
{
  state = Disconnected;
  if (closeCallback)
  {
    closeCallback(shared_from_this());
  }
}

void TcpConnect::writeEvent() {}

void TcpConnect::connectHandle()
{
  state = Connected;
  event->enableReading();
  // event->enableError();
}

void TcpConnect::write(const char *data)
{
  int len=strlen(data);
  //TODO
}

void TcpConnect::write(const string &data)
{

}

void TcpConnect::errorEvent()
{
  
}