#include <iostream>
//#include "muduo_practice/base/Thread.h"
#include "../../base/Thread.h"
using namespace yy;
using namespace std;

class MyThread:public Thread{
public:
  virtual void run() override{
    cout<<"in run\n";
  }
};

int main()
{
  MyThread mth;
  mth.start();

  mth.join();

}
