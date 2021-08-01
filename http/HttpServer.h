#pragma once
#include "../net/TcpServer.h"
#include "./HttpRequest.h"
#include "./HttpResponse.h"

namespace yy
{
class HttpServer : public TcpServer
{
public:
  HttpServer(EventLoop *loop, SocketAddr &addr);
  ~HttpServer();

private:
  virtual void connectCallback(TcpConnect::ptr tcpConnect) override;
  virtual void messageCallback(TcpConnect::ptr tcpConnect,
                               Buffer &buffer) override;
  virtual void writeCompleteCallback(TcpConnect::ptr TcpConnect) override;
  virtual void connectCloseCallback(TcpConnect::ptr TcpConnect) override;

  virtual void httpCallback(const HttpRequest &, HttpResponse *);
  void onRequest(std::shared_ptr<TcpConnect> conn, const HttpRequest &request);
};
} // namespace yy