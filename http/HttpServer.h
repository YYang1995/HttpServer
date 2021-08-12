#pragma once
#include <functional>

#include "../net/TcpServer.h"
#include "./HttpRequest.h"
#include "./HttpResponse.h"

namespace yy
{
class HttpServer
{
 public:
  using HttpCallBack =
      std::function<void(const yy::HttpRequest &, yy::HttpResponse *)>;

  HttpServer(EventLoop *loop, SocketAddr &addr);
  ~HttpServer();
  void start();
  void setHttpCallback(const HttpCallBack &cb)
  {
    httpCallback_=cb;
  }
 private:
  void connectCallback(TcpConnect::ptr tcpConnect);
  void messageCallback(TcpConnect::ptr tcpConnect, Buffer &buffer);
  void writeCompleteCallback(TcpConnect::ptr TcpConnect);
  // void connectCloseCallback(TcpConnect::ptr TcpConnect);

  void defaultHttpCallback(const HttpRequest &request, HttpResponse *);
  void onRequest(std::shared_ptr<TcpConnect> conn, const HttpRequest &request);

 private:
  TcpServer server_;
  HttpCallBack httpCallback_;
};
}  // namespace yy