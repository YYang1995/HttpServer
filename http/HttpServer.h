#pragma once
#include <functional>

#include "../net/TcpServer.h"
#include "./HttpRequest.h"
#include "./HttpResponse.h"
#include "../net/Buffer.h"

namespace http
{
class HttpServer
{
 public:
  using HttpCallBack =
      std::function<void(const HttpRequest &, HttpResponse *)>;

  HttpServer(net::EventLoop *loop, net::SocketAddr &addr);
  ~HttpServer();
  void start();
  void setHttpCallback(const HttpCallBack &cb)
  {
    httpCallback_=cb;
  }
 private:
  void connectCallback(net::TcpConnect::ptr tcpConnect);
  void messageCallback(net::TcpConnect::ptr tcpConnect, net::Buffer &buffer);
  void writeCompleteCallback(net::TcpConnect::ptr TcpConnect);
  // void connectCloseCallback(TcpConnect::ptr TcpConnect);

  void defaultHttpCallback(const HttpRequest &request, HttpResponse *);
  void onRequest(std::shared_ptr<net::TcpConnect> conn, const HttpRequest &request);

 private:
  net::TcpServer server_;
  HttpCallBack httpCallback_;
};
}  // namespace http