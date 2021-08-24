#include "TcpConnect.h"

#include <assert.h>
#include <unistd.h>

#include <iostream>

#include "../base/ALog.h"
#include "SocketOperation.h"

using namespace base;
using namespace net;
using namespace std;

TcpConnect::TcpConnect(EventLoop *loop, SocketAddr &a, int fd)
    : loop(loop),
      addr(a),
      name(addr.ipToString() + ":" + addr.portToString()),
      channel_(new Channel(loop, fd)),
      socket_(new Socket(fd)),
      state(Disconnected)
{
  setNoDelay();
  // loop->updateChannel(channel_.get());  在TcpServer::newConnected中执行
  channel_->setReadCallback(std::bind(&TcpConnect::readEvent, this));
  channel_->setWriteCallback(std::bind(&TcpConnect::writeEvent, this));
  channel_->setErrorCallback(std::bind(&TcpConnect::errorEvent, this));
  channel_->setCloseCallback(std::bind(&TcpConnect::closeEvent, this));
  socket_->setKeepAlive(true);
}

TcpConnect::~TcpConnect()
{
  assert(state == Disconnected);
  LOG_INFO("TcpConnect [%s] disconnect.",name.c_str());
}

void TcpConnect::setNoDelay() { socket_->setTcpNoDelay(); }

void TcpConnect::shutDownWrite()
{
  loop->assertInLoopThread();
  if (state == Connected)
  {
    state = Disconnecting;
    if (!channel_->isWriting())
    {
      socket_->shutDownWrite();
    }
  }
}

void TcpConnect::readEvent()
{
  int error = 0;
  int n = readBuffer.readFromIO(channel_->fd(), error);
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
    LOG_ERROR("TcpConnect::readEvent() error! Error messsge= %s",
              strerror(errno));
    errorEvent();
  }
}

void TcpConnect::closeEvent()
{
  assert(state == Connected || state == Disconnecting);
  setState(Disconnected);
  channel_->disableAll();
  if (closeCallback_)
  {
    //从Tcp连接池中移除;
    closeCallback_(shared_from_this());
  }
}

//从writeBuffer中向event->fd()中写数据
void TcpConnect::writeEvent()
{
  loop->assertInLoopThread();
  if (channel_->isWriting())
  {
    auto n = SocketOperation::write(channel_->fd(), writeBuffer.readIndexPtr(),
                                    writeBuffer.writeableBytes());
    if (n > 0)
    {
      writeBuffer.updateReadIndex(n);
      if (writeBuffer.isEmpty())
      {
        // LT 避免频繁触发EPOLLOUT
        channel_->disableWritinkg();
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
      LOG_ERROR("TcpConnect::writeEvent() error! Error message= %s",
                strerror(errno));
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
    LOG_ERROR(
        "TcpConnect::write(const void*,unit32_t) error! disconnected,give up "
        "writeing");
    return;
  }
  if (!channel_->isWriting() && writeBuffer.readableBytes() == 0)
  {
    //直接写入fd，剩下的加入writeBuffer
    hasWriten = SocketOperation::write(channel_->fd(), data, len);
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
        LOG_ERROR(
            "TcpConnect::write(const void* ,uint32_t) error! Error message= %s",
            strerror(errno));
      }
    }
  }
  writeBuffer.append(static_cast<const char *>(data) + hasWriten,
                     remaining);  //必须用类型转换
  if (!channel_->isWriting())
  {
    channel_->enableWriting();
  }
}

void TcpConnect::send(const string &data) { write(&*data.begin()); }

void TcpConnect::errorEvent() { LOG_ERROR("TcpConnect::errorEvent()"); }

void TcpConnect::connectDestroyed()
{
  setState(Disconnected);
  // channel_->disableAll();
  channel_->remove();
}

void TcpConnect::connectEstablished()
{
  assert(state = Connecting);
  setState(Connected);
  channel_->enableReading();
  if (connectionCallback_) connectionCallback_(shared_from_this());
}