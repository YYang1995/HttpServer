#include "HttpResponse.h"
#include "../net/Buffer.h"

using namespace std;
using namespace yy;

HttpResponse::HttpResponse():version_("HTTP/1.1"),statusCode_(UnKnown){}

HttpResponse::~HttpResponse(){}

void HttpResponse::setStatusCode(const StatusCode &code){
    statusCode_=code;
}

void HttpResponse::setStatusMessage(const string &msg){
    statusMessage_=msg;
}

void HttpResponse::setCloseConnection(const bool &on){
    closeConnection_=on;
}

bool HttpResponse::getCloseConnection() const{
    return closeConnection_;
}

void HttpResponse::setContentType(const string &type){
    addHeader("Content-type",type);
}

void HttpResponse::addHeader(const string &key,const string &value){
    headers_[key]=value;
}

void HttpResponse::setBody(const string &body){
    this->body_=body;
}

void HttpResponse::addToBuffer(Buffer *output){
    char buffer[32]={0};
    snprintf(buffer,sizeof(buffer),"HTTP/1.1 %d",statusCode_);
    output->append(buffer);
    output->append(statusMessage_);
    output->append("\r\n");
    //add headers
    //判断是否是最后的信息
    if(closeConnection_){
        output->append("Connect: close\r\n");
    }else{
        snprintf(buffer,sizeof(buffer),"Content-Length: %zd\r\n",body_.size());
        output->append(buffer);
        output->append("Connection: Keep-Alive\r\n");
    }
    for(auto iter:headers_){
        output->append(iter.first);
        output->append(": ");
        output->append(iter.second);
        output->append("\r\n");
    }
    output->append("\r\n");
    output->append(body_);

}