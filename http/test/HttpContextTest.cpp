#include "../HttpContext.h"
#include "../../net/Buffer.h"
#include "../HttpRequest.h"
#include "../HttpResponse.h"

#include <iostream>
#include <string>

using namespace std;
using namespace yy;

int main() {
  Buffer buffer;
  HttpResponse response(true);
  response.setStatusCode(HttpResponse::StatusCode::_200OK);
  response.setStatusMessage("OK");
  response.setCloseConnection("Text/Html");
  response.addHeader("Server", "localhost");
  response.setBody("test function of HttpResponse");
  response.addToBuffer(&buffer);
}