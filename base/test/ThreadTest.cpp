#include "../Thread.h"
#include <iostream>

using namespace base;
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
  myThread->join();  
  cout<<"thread id ="<<myThread->getNowThreadId()<<endl;
}
