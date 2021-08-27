#include <memory>
#include <mutex>
#include <atomic>

namespace base
{
//懒汉式线程安全单例
template <typename T>
class SingleTon
{
 public:
  static T* GetInstance()
  {
    if (SingleTon::obj == nullptr)
    {
      std::lock_guard<std::mutex> guard(mtx);
      if (SingleTon::obj == nullptr)
      {
        SingleTon::obj = new T();
      }
    }

    return SingleTon::obj;
  }

  static void Destory() { delete SingleTon::obj; }

 private:
  SingleTon();
  ~SingleTon();
  SingleTon(const SingleTon&) ;
  SingleTon& operator=(const SingleTon&) ;

 private:
  static T* obj;
  static std::mutex mtx;
};
template <typename T>
T* SingleTon<T>::obj = nullptr;
template <typename T>
std::mutex SingleTon<T>::mtx;
}  // namespace base
