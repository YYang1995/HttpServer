#include "HttpServer.h"

#include <time.h>

#include <iostream>

#include "../net/Buffer.h"
#include "HttpContext.h"
#include "../base/ALog.h"
#include "../net/TcpServer.h"

using namespace std;
using namespace http;
using namespace net;
using namespace base;

HttpServer::HttpServer(EventLoop *loop, SocketAddr &addr)
    : server_(loop, addr), httpCallback_(nullptr)
{
  server_.setConnnectCallback(
      std::bind(&HttpServer::connectCallback, this, std::placeholders::_1));
  server_.setMessageCallback(std::bind(&HttpServer::messageCallback, this,
                                       std::placeholders::_1,
                                       std::placeholders::_2));
  // server_.setWriteCompleteCallback(std::bind(&HttpServer::writeCompleteCallback,
  //                                            this, std::placeholders::_1));
}

HttpServer::~HttpServer() {}

void HttpServer::start()
{
  LOG_INFO( "HttpServer start()!");
  server_.start();
}

void HttpServer::connectCallback(const TcpConnect::ptr &TcpConnect) {}

void HttpServer::messageCallback(const TcpConnect::ptr &tcpConnect,
                                 net::Buffer &buffer)
{
  HttpContext context;
  time_t now_sec = time(0);
  char *now = ctime(&now_sec);
  string now_str(now);
  if (!context.parseRequest(&buffer, now_str))
  {
    tcpConnect->send("HTTP/1.1 400 Bad Request\r\n\r\n");
    tcpConnect->shutDownWrite();
  }
  if (context.isParseAll())
  {
    auto temp = context.getRequest();
    onRequest(tcpConnect, context.getRequest());
    context.reset();
  }
}

void HttpServer::writeCompleteCallback(TcpConnect::ptr tcpConnect) {}

void HttpServer::defaultHttpCallback(const HttpRequest &request,
                                     HttpResponse *response)
{
  response->setStatusCode(HttpResponse::_400BadRequest);
  response->setStatusMessage("Not Found");
  response->setCloseConnection(true);
}

void HttpServer::onRequest(std::shared_ptr<TcpConnect> conn,
                           const HttpRequest &request)
{
  const string connection = request.getHeader("Connection");
  //短连接
  bool close =
      (connection == "close" || (request.getVersion() == HttpRequest::Http10 &&
                                 connection != "Keep-Alive"));

  HttpResponse response(close);
  if (httpCallback_)
  {
    httpCallback_(request, &response);
  }
  else
  {
    this->defaultHttpCallback(request, &response);
  }
  Buffer buffer;
  response.addToBuffer(&buffer);
  string str;
  buffer.readAllAsString(str);
  conn->send(str);
  //短链接则直接关闭
  if (response.getCloseConnection())
  {
    conn->shutDownWrite();
  }
}