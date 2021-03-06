#include <iostream>
#include <string>

#include "../../net/Buffer.h"
#include "../HttpContext.h"
#include "../HttpRequest.h"
#include "../HttpResponse.h"


using namespace std;
using namespace net;
using namespace http;

int main()
{
  Buffer buffer;
  HttpResponse response(true);
  response.setStatusCode(HttpResponse::StatusCode::_200OK);
  response.setStatusMessage("OK");
  response.setCloseConnection("Text/Html");
  response.addHeader("Server", "localhost");
  response.setBody("test function of HttpResponse");
  response.addToBuffer(&buffer);
}