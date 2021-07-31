#pragma once
#include <map>
#include <string>
#include <map>

namespace yy{
class HttpRequest{
public:
  enum Method{
    Invalid,
    GET,
    POST,
    HEAD,
    PUT
//    DELETE
  };
  enum Version{
    Unknown,
    Http10,
    Http11
  };

public:
  HttpRequest();
  ~HttpRequest(){};

  Version getVersion() const;
  void setVersion(const Version &version);

  Method getMethod() const;
  bool setMethod(const char *begin,const char *end); //返回bool判断是否成功
  const char* methodString(); //把method转为char*

  void setPath(const char *begin,const char *end);
  const std::string& getPath() const;

  void setQuery(const char *start,const char *end);
  const std::string& getQuery() const;

  void setReceivedTime(const std::string &t);
  const std::string& getReceivedTime() const;

  //[start,colon]域的位置
  //[colon,end]值的位置
  bool addHeader(const char *start,const char *colon,const char *end);
  //参数为header的key
  std::string getHeader(const std::string &field) const;
  //获取所有的头
  const std::map<std::string,std::string>& getHeaders() const ;

  void swap(HttpRequest &another);

private:
  Method method_;
  Version version_;
  std::string path_;
  std::string query_;
  std::string receivedTime_;
  std::map<std::string,std::string> headers_;
};
}