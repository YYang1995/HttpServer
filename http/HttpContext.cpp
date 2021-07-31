#include "HttpContext.h"

#include <algorithm>

#include "../net/Buffer.h"

using namespace yy;
using namespace std;

HttpContext::HttpContext() : state_(ExpectRequestLine) {
}

bool HttpContext::gotAll() {
  return state_ == GotAll;
}

void HttpContext::reset() {
  state_ = ExpectRequestLine;
  HttpRequest temp;
  temp.swap(request_);
}

HttpRequest &HttpContext::getRequest() {
  return request_;
}

bool HttpContext::parseRequest(Buffer *buffer, string receiveTime) {
  bool hasMore = true;
  bool res = true;
  while (hasMore)
  {
    switch (state_)
    {
      case ExpectRequestLine:
      {
        const char *crlf = buffer->findCRLF();
        if (crlf)
        {
          res = processRequestLine(buffer->readIndexPtr(), crlf);
          if (res)
          {
            request_.setReceivedTime(receiveTime);
            buffer->retrieveUntil(crlf + 2);
            state_ = ExpectRequestHead;
            continue;
          }
        }
        hasMore = false;

      }
      break;
      case ExpectRequestHead:
      {
        const char *crlf = buffer->findCRLF();
        if (crlf)
        {
          const char *colon = std::find(buffer->readIndexPtr(), crlf, ':');
          if (colon != crlf)
          {
            request_.addHeader(buffer->readIndexPtr(), colon, crlf);
          } else
          {
            state_ = GotAll;
            hasMore = false;
          }
          buffer->retrieveUntil(crlf + 2);
          continue;
        }
        hasMore=false;
      }
      break;
      case ExpectRequestBody:
      {
        //直接保存在buffer中，不解析
      } break;
      default:
        break;
    }
  }
  return res;
}

bool HttpContext::processRequestLine(const char *begin, const char *end) {
  bool succeed = false;
  const char *pos = begin;
  const char *space = std::find(pos, end, ' ');
  if (space != end && request_.setMethod(pos, space)) {
    pos = space + 1;
    space = std::find(pos, end, ' ');
    if (space != end) {
      const char *question_mark = std::find(pos, space, '?');
      if (question_mark == space) {
        request_.setPath(pos, question_mark);
      } else {
        request_.setPath(pos, question_mark);
        request_.setQuery(question_mark, space);
      }
    }
    pos = space + 1;
    succeed = end - pos == 8 && std::equal(pos, end - 1, "HTTP/1.");
    if (succeed) {
      if (*(end - 1) == '1') {
        request_.setVersion(HttpRequest::Http11);
      } else if ((*end - 1) == '0') {
        request_.setVersion(HttpRequest::Http10);
      } else {
        succeed = false;
      }
    }
  }
  return succeed;
}