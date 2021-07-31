#include "../HttpContext.h"
#include "../../net/Buffer.h"
#include <assert.h>
#include <string>
#include <iostream>
#include "../HttpRequest.h"

using namespace std;
using namespace yy;

int main()
{
//  Buffer buffer;
  string stimu_request="GET www.baidu.com http/1.1\r\n";
//  buffer.append(stimu_request);
//  HttpContext context;
////  auto result=context.parseRequest(&buffer,"132");
  const char *str=stimu_request.c_str();
//  context.processRequestLine(str,str+4);
//
//
//  auto request=context.getRequest();
//
//  cout<<request.getMethod()<<endl;
//  cout<<request.getVersion()<<endl;
//  cout<<request.getPath()<<endl;

  HttpContext context;
  cout<<context.gotAll()<<endl;

}