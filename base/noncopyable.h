#pragma once
namespace base
{
class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  noncopyable& operator=(const noncopyable&) = delete;
  noncopyable() = default;
  ~noncopyable() = default;
};
}  // namespace base