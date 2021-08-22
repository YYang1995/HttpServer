#pragma once
#include <algorithm>
#include <string>

#include "../net/Buffer.h"
#include "HttpRequest.h"

namespace http
{
class HttpContext
{
 public:
  enum ParseState
  {
    ExpectRequestLine,  //请求行
    ExpectRequestHead,  //请求头
    ExpectRequestBody,  //请求头
    GotAll              //解析完毕
  };

 public:
  HttpContext();
  ~HttpContext() = default;
  bool isParseAll();  //判断是否解析完毕
  void reset();  //将状态转为初始状态，同时清空需要解析的报文
  HttpRequest &getRequest();
  bool parseRequest(net::Buffer *buffer, std::string receiveTime);

 private:
  bool processRequestLine(const char *begin, const char *end);
  ParseState state_;
  HttpRequest request_;
};
}  // namespace http