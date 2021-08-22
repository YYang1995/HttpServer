#include "TcpConnect.h"

#include <assert.h>
#include <unistd.h>

#include <iostream>

#include "SocketOperation.h"

using namespace net;
using namespace std;

TcpConnect::TcpConnect(EventLoop *loop, SocketAddr &a, int fd)
    : loop(loop),
      addr(a),
      name(addr.ipToString() + " : " + addr.portToString()),
      event(new Channel(loop, fd)),
      socket(new Socket(fd)),
      state(Disconnected)
{
  setNoDelay();
  // loop->updateChannel(event.get());  在TcpServer::newConnected中执行
  event->setReadCallback(std::bind(&TcpConnect::readEvent, this));
  event->setWriteCallback(std::bind(&TcpConnect::writeEvent, this));
  event->setErrorCallback(std::bind(&TcpConnect::errorEvent, this));
  event->setCloseCallback(std::bind(&TcpConnect::closeEvent, this));
  socket->setKeepAlive(true);
}

TcpConnect::~TcpConnect()
{
  assert(state == Disconnected);
  // event->disableAll();
  //  event->removeEvnet(shared_from_this()); TODO
}

void TcpConnect::setNoDelay() { socket->setTcpNoDelay(); }

void TcpConnect::shutDownWrite()
{
  loop->assertInLoopThread();
  if (state == Connected)
  {
    state = Disconnecting;
    if(!event->isWriting())
    {
      socket->shutDownWrite();
    }
  }
}

void TcpConnect::readEvent()
{
  int error = 0;
  int n = readBuffer.readFromIO(event->fd(), error);
  if (n > 0)
  {
    if (messageCallback_)
    {
      messageCallback_(shared_from_this(), readBuffer);
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
    errorEvent();
  }
}

void TcpConnect::closeEvent()
{
  assert(state == Connected || state == Disconnecting);
  setState(Disconnected);
  event->disableAll();
  if (closeCallback_)
  {
    closeCallback_(shared_from_this());
  }
}

//从writeBuffer中向event->fd()中写数据
void TcpConnect::writeEvent()
{
  loop->assertInLoopThread();
  if (event->isWriting())
  {
    auto n = SocketOperation::write(event->fd(), writeBuffer.readIndexPtr(),
                                    writeBuffer.writeableBytes());
    if (n > 0)
    {
      writeBuffer.updateReadIndex(n);
      if (writeBuffer.isEmpty())
      {
        // LT 避免频繁触发EPOLLOUT
        event->disableWritinkg();
        if (writeCompleteCallback_)
        {
          // writeCompleteCallback_(shared_from_this());
          loop->queueInLoop(
              std::bind(writeCompleteCallback_, shared_from_this()));
        }
      }
    }
    else
    {
      cout << "TcpConnect::writeEvent() errno= " << strerror(errno) << endl;
    }
  }
}

void TcpConnect::connectHandle() { state = Connected; }

void TcpConnect::write(const char *data) { write(data, strlen(data)); }

void TcpConnect::write(const void *data, uint32_t len)
{
  loop->assertInLoopThread();
  ssize_t hasWriten = 0;
  int n = 0;
  auto remaining = len;
  if (state == Disconnected)
  {
    cerr << "disconnected,give up writeing\n";
    return;
  }
  if (!event->isWriting() && writeBuffer.readableBytes() == 0)
  {
    //直接写入fd，剩下的加入writeBuffer
    hasWriten = SocketOperation::write(event->fd(), data, len);
    if (hasWriten > 0)
    {
      remaining = len - hasWriten;
      if (remaining == 0 && writeCompleteCallback_)
      {
        loop->runInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
      }
    }
    else
    {
      if (errno != EWOULDBLOCK)
      {
        cout << "TcpConnect::write(const void* ,uint32_t)\n";
      }
    }
  }
  writeBuffer.append(static_cast<const char *>(data) + hasWriten,
                     remaining);  //必须用类型转换
  if (!event->isWriting())
  {
    event->enableWriting();
  }
}

void TcpConnect::send(const string &data) { write(&*data.begin()); }

void TcpConnect::errorEvent() { cerr << "TcpConnect::errorEvent()\n"; }

void TcpConnect::connectDestroyed()
{
  setState(Disconnected);
  event->disableAll();
  loop->removeChannel(event.get());
}

void TcpConnect::connectEstablished()
{
  assert(state = Connecting);
  setState(Connected);
  event->enableReading();
  if (connectionCallback_) connectionCallback_(shared_from_this());
}