#include "HttpServer.h"
#include "HttpContext.h"
#include <time.h>

using namespace std;
using namespace yy;

HttpServer::HttpServer(EventLoop *loop, SocketAddr &addr)
    : TcpServer(loop, addr)
{
}

HttpServer::~HttpServer() {}

void HttpServer::connectCallback(TcpConnect::ptr TcpConnect) {}

void HttpServer::messageCallback(TcpConnect::ptr tcpConnect, Buffer &buffer)
{
  HttpContext context;
  time_t now_second = time(0);
  char *now = ctime(&now_second);
  string now_str(now);
  if (!context.parseRequest(&buffer, now_str))
  {
  }
  if (context.gotAll())
  {
    onRequest(tcpConnect, context.getRequest());
    context.reset();
  }
}

void HttpServer::writeCompleteCallback(TcpConnect::ptr tcpConnect) {}

void HttpServer::connectCloseCallback(TcpConnect::ptr tcpConnect) {}

void HttpServer::httpCallback(const HttpRequest &request,
                              HttpResponse *response)
{
  response->setStatusCode(HttpResponse::_400BadRequest);
  response->setStatusMessage("Not Found");
  response->setCloseConnection(true);
}

void HttpServer::onRequest(std::shared_ptr<TcpConnect> conn,
                           const HttpRequest &request)
{
  const string &connection = request.getHeader("Connection");
  //短连接
  bool close =
      (connection == "close" || (request.getVersion() == HttpRequest::Http10 &&
                                 connection != "Keep-Alive"));
  HttpResponse response(close);
  httpCallback(request, &response);
  Buffer buffer;
  response.addToBuffer(&buffer);
  string str;
  buffer.readAllAsString(str);
  conn->write(str);
  //短链接则直接关闭
  if(response.getCloseConnection())
  {
    conn->shutDownWrite();
  }
}