#pragma once
#include <stdint.h>

#include <string>
#include <vector>


namespace yy
{
class Buffer
{
 public:
  static const int DefaultSize;
  Buffer(int size = DefaultSize);
  ~Buffer(){};
  int readFromIO(int fd, int &errNo);
  uint32_t writeableBytes();  //还剩多少空间可以写
  uint32_t readableBytes();
  bool isReadable();
  bool isEmpty();
  void ensureWriteableBytes(std::size_t len);
  void append(const char *data, std::size_t len);
  void append(const std::string &str);
  void swap(Buffer &rhs);

  const char *readIndexPtr() const;
  void resetIndex();
  void updateReadIndex(uint32_t len);  //更新readIndex
  void readAllAsString(
      std::string &readBuff);  //把buffer中数据全部读入readBuffer
  void readAsString(std::string &readBuf, uint32_t len);
  int readBytes(std::vector<char> &data, uint32_t len);
  // HTTP用
  const char *findCRLF() const;
  //清空
  void retrieveUntil(const char *end);

 private:
  std::vector<char> buffer;
  uint32_t readIndex;
  uint32_t writeIndex;
  const char *bufferPtr() const { return &(*buffer.begin()); }
};
}  // namespace yy