#include "../Thread.h"
#include <iostream>

using namespace yy;
using namespace std;

class MyThread:public Thread
{
  public:
    virtual void run() override
    {
      cout<<"in MyThread\n";
    }
};
int main()
{
  MyThread *myThread=new MyThread();
  myThread->start();
  myThread->join();  //需要手动join是否不妥？
}
