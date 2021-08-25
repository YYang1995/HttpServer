#include <iostream>

#include "../HttpServer.h"
#include "../../base/ALog.h"
#include "../../net/Buffer.h"
#include "../HttpContext.h"
#include <unistd.h>
#include <fcntl.h>
#include "../HttpRequest.h"
#include "../HttpResponse.h"

using namespace std;
using namespace http;
using namespace base;
using namespace net;


void test(const HttpRequest &request, HttpResponse *response)
{
  response->setStatusCode(HttpResponse::_200OK);
  response->setStatusMessage("OK");
  response->setContentType("text/html");
  response->addHeader("Server","ubuntu");
  string body;
  body.append("<h1>自己没什么博客，就放一些收藏的博客吧</h1>");
  body.append("<a href='https://www.cnblogs.com/coderzh/archive/2009/04/06/1426755.html'>Google Test</a><p>");
  body.append("<a href='https://www.cnblogs.com/huxiao-tee/p/4660352.html'>mmap</a><p>");
  body.append("<a href='https://www.cnblogs.com/sench/p/8933638.html'>umak</a><p>");
  body.append("<a href='http://www.https://www.cnblogs.com/x_wukong/p/10848069.html.com'>errno数值意义</a><p>");
  response->setBody(body);
  // response->setCloseConnection(true);
}

void test2(const HttpRequest &request, HttpResponse *response)
{
  int fd=::open("../html/index.html",O_RDONLY);
  if(fd==-1)
  {
    cout<<"open error\n";
    return ;
  }
  string body;
  char msg[1024];
  int len;
  while((len=read(fd,msg,sizeof msg))>0)
  {
    msg[len]='\0';
    body.append(msg);
  }
  response->setBody(body);
}
int main()
{
  ALog::init(nullptr,false);
  EventLoop loop;
  SocketAddr addr(4220);
  HttpServer server(&loop, addr);
  server.setHttpCallback(test2);
  server.start();
  loop.loop();
  ALog::shutdown();
}