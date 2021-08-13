#include <string.h>

#include <iostream>

#include "../HttpServer.h"

using namespace std;
using namespace yy;

void test(const HttpRequest &request, HttpResponse *response)
{
  response->setStatusCode(HttpResponse::_200OK);
  response->setStatusMessage("OK");
  response->setContentType("text/html");
  response->addHeader("Server","ubuntu");
  string body;
  body.append("<a href='http://www.baidu.com'>baidu</a>");
  body.append("<h1>hi</h1>");
  response->setBody(body);
  // response->setCloseConnection(true);
}
int main()
{
  EventLoop loop;
  SocketAddr addr(4220);
  HttpServer server(&loop, addr);
  server.setHttpCallback(test);
  server.start();
  loop.loop();
}