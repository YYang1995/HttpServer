#pragma once
#include <map>
#include <string>
#include "../net/Buffer.h"

namespace http
{

class HttpResponse
{
 public:
  enum StatusCode
  {
    UnKnown = 0,
    _200OK = 200,
    _301MovedPermanently = 301,
    _400BadRequest = 400,
    _404NotFound = 404
  };
  HttpResponse(const bool &close);
  ~HttpResponse();
  void setStatusCode(const StatusCode &code);
  void setStatusMessage(const std::string &msg);
  void setCloseConnection(const bool &on);
  bool getCloseConnection() const;
  //设置content类型
  void setContentType(const std::string &type);
  void addHeader(const std::string &key, const std::string &value);
  void setBody(const std::string &body);
  void addToBuffer(net::Buffer *output);

 private:
  std::string version_;
  StatusCode statusCode_;
  std::string statusMessage_;
  //主体
  std::string body_;
  std::map<std::string, std::string> headers_;
  std::string responseBody_;
  // TODO 关闭信息？
  bool closeConnection_;
};
}  // namespace http
