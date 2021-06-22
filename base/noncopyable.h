#pragma once
namespace yy{
class noncopyable{
public:
  noncopyable(const noncopyable&)=delete;
  noncopyable& operator=(const noncopyable&)=delete;
  noncopyable()=default;
  ~noncopyable()=default;
};
}