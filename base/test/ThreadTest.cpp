#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

#include <iostream>

#include "../CountDownLatch.h"
#include "../Thread.h"
#include "../Thread.cpp"

using namespace base;
using namespace std;

CountDownLatch latch(1);
class MyThread : public Thread
{
 public:
  MyThread(string name) : Thread(name) {}
  virtual void run() override
  {
    cout << "in MyThread\n";
    cout << "process id =" << getpid() << endl;
    cout << "another id= " << syscall(__NR_gettid) << endl;
    cout << "--------------\n";
    latch.signal();
  }
};
int main()
{
  MyThread myThread("work");
  myThread.start();
  latch.wait();
  cout << "thread id =" << myThread.getThreadId() << endl;
  cout << "process id =" << getpid() << endl;
  cout << "another id= " << syscall(__NR_gettid) << endl;
  cout << "thread name= " << myThread.getName() << endl;
  cout << "thraed name prefix= " << myThread.getNamePrefix() << endl;
  myThread.join();
}
