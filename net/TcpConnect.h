#pragma once
#include "Buffer.h"
#include "EventLoop.h"
#include "Socket.h"
#include <string>
#include <memory.h>

namespace yy{
class TcpConnect:public std::enable_shared_from_this<TcpConnect>{
public:
  typedef std::shared_ptr<TcpConnect> ptr;
  typedef std::function<void(std::shared_ptr<TcpConnect>,Buffer&)> MessageCallback;
  typedef std::function<void(std::shared_ptr<TcpConnect>)> WriteCompleteCallback;
  typedef std::function<void(std::shared_ptr<TcpConnect>)> CloseCallback;

  enum ConnectState{
    Disconnected,
    Connecting,
    Connected,
    Disconnecting
  };

public:
  TcpConnect(EventLoop *loop,SocketAddr &a,int fd);
  ~TcpConnect();

  void setMessageCallback(const MessageCallback &callback){messageCallback=callback;};
  void setCloseCallback(const CloseCallback &callback){closeCallback=callback;}
  void setWriteCompleteCallback(const WriteCompleteCallback &callback){writeCompleteCallback=callback;};


  SocketAddr& getAddr(){return addr;}
  const std::string getName() const {return name;}

  void setNoDelay();
  void shutDownWrite();

  void write(const char *data);
  void write(const std::string &data);
  void write(const void *data,uint32_t len);
  void connectHandle();

private:
  EventLoop *loop;
  SocketAddr addr;
  std::string name;
  std::shared_ptr<Socket> socket;
  std::shared_ptr<Channel> event;

  MessageCallback messageCallback;
  CloseCallback closeCallback;
  WriteCompleteCallback writeCompleteCallback;

  int state;

  Buffer readBuffer;
  Buffer writeBUffer;

  void readEvent();
  void closeEvent();
  void writeEvent();
  void errorEvent();
};
}