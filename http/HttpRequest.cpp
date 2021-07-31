#include "HttpRequest.h"

using namespace yy;
using namespace std;

using Version=HttpRequest::Version;
using Method=HttpRequest::Method;

HttpRequest::HttpRequest():method_(Invalid),version_(Unknown) {

}

void HttpRequest::setVersion(const Version &version) {
  version_=version;
}

Version HttpRequest::getVersion() const {
  return version_;
}

bool HttpRequest::setMethod(const char *begin,const char *end) {
  if(!method_)
    return false;
  string method=string(begin,end);
  if(method=="GET"){
    method_=GET;
  }else if(method=="POST"){
    method_=POST;
  }else if(method=="HEAD"){
    method_=HEAD;
  }else if(method=="PUT"){
    method_=PUT;
  }else{
    method=Invalid;
  }
  return method_;
}

Method HttpRequest::getMethod() const {
  return method_;
}

const char* HttpRequest::methodString() {
  const char *result="UNKNOW";
  switch(method_){
    case GET:
      result="GET";
      break;
    case POST:
      result="POST";
      break;
    case HEAD:
      result="HEAD";
      break;
    case PUT:
      result="PUT";
      break;
    default:
      break;
  }
  return result;
}

void HttpRequest::setPath(const char *begin, const char *end) {
  path_.assign(begin,end);
}

const string& HttpRequest::getPath() const {
  return path_;
}

void HttpRequest::setQuery(const char *start, const char *end) {
  query_.assign(start,end);
}

const string& HttpRequest::getQuery() const {
  return query_;
}

void HttpRequest::setReceivedTime(const std::string &t) {
  receivedTime_=t;
}

const string& HttpRequest::getReceivedTime() const {
  return receivedTime_;
}

bool HttpRequest::addHeader(const char *start, const char *colon, const char *end) {
  string field(start,colon);
  //去除空格
  for(;colon!=end && isspace(*colon);colon++){}
  if(colon==end) return false;
  string value(colon,end);
  //TODO 下面一行的作用？
  for(;!value.empty() && isspace(value[value.size()-1]);value.resize(value.size()-1) );
  headers_[field]=value;
}

string HttpRequest::getHeader(const std::string &field) const {
  string result;
  auto iter=headers_.find(field);
  if(iter!=headers_.end()){
    result=iter->second;
  }
  return result;
}

const map<string,string>& HttpRequest::getHeaders() const {
  return headers_;
}

void HttpRequest::swap(HttpRequest &another) {
  if(this==&another)
    return;
  std::swap(method_,another.method_);
  std::swap(version_,another.version_);
  path_.swap(another.path_);
  query_.swap(another.query_);
  receivedTime_.swap(another.receivedTime_);
  headers_.swap(another.headers_);
}
