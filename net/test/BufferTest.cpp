#include "../Buffer.h"
#include <iostream>

using namespace std;
using namespace yy;

int main()
{
  Buffer buffer;
  buffer.append("GET www.baidu.com http/1.1\r\n");
  auto ptr=buffer.readIndexPtr();
  cout<<ptr<<endl;
  cout<<buffer.readableBytes()<<endl;
}