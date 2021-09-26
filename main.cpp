#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

#include "base/ALog.h"
#include "http/HttpContext.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "http/HttpServer.h"
#include "net/Buffer.h"
#include "base/SingleTon.h"

using namespace std;
using namespace http;
using namespace base;
using namespace net;

void demo(const HttpRequest &request, HttpResponse *response)
{
  int fd = ::open("./html/index.html", O_RDONLY);
  if (fd == -1)
  {
    cout << "open error\n";
    return;
  }
  string body;
  char msg[1024];
  int len;
  while ((len = read(fd, msg, sizeof msg)) > 0)
  {
    msg[len] = '\0';
    body.append(msg);
  }
  response->setBody(body);
}
void server_exit(int signo)
{
  cout<<"Server receive signal "<<signo<<" to exit \n";
  ALog::shutdown();
  
}
int main()
{
  signal(SIGINT,server_exit);

  ALog::init(nullptr,false);
  EventLoop loop;
  SocketAddr addr(4220);

  HttpServer server(&loop, addr);
  server.setHttpCallback(demo);
  server.start();
  loop.loop();

}