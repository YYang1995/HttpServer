#include "../SingleTon.h" 
#include <iostream>

using namespace std;
using namespace base;

class A
{
  public:
     void show()
     {
       cout<<"i'm a"<<endl;
     }
};
int main()
{
  A *p=SingleTon<A>::GetInstance() ;
  p->show();
  SingleTon<A>::Destory();
}