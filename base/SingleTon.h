#include <atomic>
#include <memory>
#include <mutex>

namespace base
{
//懒汉式线程安全单例
template <typename T>
class SingleTon
{
 public:
  static T& GetInstance()
  {
    if (instance_ == nullptr)
    {
      instance_ = new T();
    }
    return *instance_;
  }
  static void init()
  {
    instance_=new T();
  }
  static void destroy()
  {
    delete instance_;
  }
 private:
  SingleTon();
  ~SingleTon() = default;
  SingleTon(const SingleTon&);
  SingleTon& operator=(const SingleTon&);

 private:
  static T* instance_;
};

}  // namespace base
