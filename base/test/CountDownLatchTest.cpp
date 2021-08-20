#include <unistd.h>

#include <iostream>
#include <thread>

#include "../CountDownLatch.h"

using namespace std;
using namespace base;

CountDownLatch latch(2);
void func1()
{
  latch.wait();
  cout << "in fucn1. I must be late\n";
}

void func2()
{
  cout << "in func2 .I will run first\n";
  sleep(3);
  latch.signal();
}
void func3()
{
  cout<<"in func3. I will run first2\n";
  sleep(4);
  latch.signal();
}
int main()
{
  std::thread t1(func1);
  std::thread t2(func2);
  std::thread t3(func3);
  t1.join();
  t2.join();
  t3.join();
}