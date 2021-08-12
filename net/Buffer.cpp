#include "Buffer.h"

#include <sys/uio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

#include "SocketOperation.h"


using namespace yy;
using namespace std;

const int Buffer::DefaultSize = 1024;

Buffer::Buffer(int size) : readIndex(0), writeIndex(0), buffer(size) {}

int Buffer::readFromIO(int fd, int &errNo)
{
  char extraBuff[65536];  //两段缓冲 64k
  struct iovec vec[2];
  uint32_t writeable = writeableBytes();
  vec[0].iov_base = &(*buffer.begin()) + writeIndex;
  vec[0].iov_len = writeable;
  vec[1].iov_base = extraBuff;
  vec[1].iov_len = sizeof(extraBuff);

  uint32_t iovcnt = (writeable < sizeof(extraBuff)) ? 2 : 1;
  int n = SocketOperation::readv(fd, vec, iovcnt);
  if (n < 0)
  {
    errNo = errno;
    cout<<"Buffer::readFromIO errno= "<<strerror(errno)<<endl;
  }
  else if ((uint32_t)n <= writeable)
  {
    writeIndex += n;
  }
  else
  {
    writeIndex = buffer.size();
    append(extraBuff, n - writeable);
  }
  return n;
}

uint32_t Buffer::writeableBytes() { return buffer.size() - writeIndex; }

uint32_t Buffer::readableBytes() { return writeIndex - readIndex; }

bool Buffer::isReadable() { return readIndex < writeIndex; }

bool Buffer::isEmpty() { return readIndex == writeIndex; }

//确保至少len长度可写？
void Buffer::ensureWriteableBytes(std::size_t len)
{
  if (writeableBytes() < len)
  {
    buffer.resize(writeIndex + len);
  }
}

void Buffer::append(const char *data, std::size_t len)
{
  ensureWriteableBytes(len);
  std::copy(data, data + len, buffer.begin() + writeIndex);
  writeIndex += len;
}

void Buffer::append(const std::string &str) { append(str.c_str(), str.size()); }

void Buffer::swap(Buffer &rhs)
{
  buffer.swap(rhs.buffer);
  std::swap(this->readIndex, rhs.readIndex);
  std::swap(this->writeIndex, rhs.writeIndex);
}

const char *Buffer::readIndexPtr() const
{
  return &(*buffer.begin()) + readIndex;
}

void Buffer::resetIndex()
{
  readIndex = 0;
  writeIndex = 0;
}

void Buffer::updateReadIndex(uint32_t len)
{
  if (len < readableBytes())
  {
    readIndex += len;
  }
  else
  {
    resetIndex();
  }
}

void Buffer::readAsString(std::string &readBuf, uint32_t len)
{
  len = std::min(readableBytes(), len);
  readBuf.assign((const char *)(readIndexPtr()), len);  
  updateReadIndex(len);
}

void Buffer::readAllAsString(std::string &readBuff)
{
  readAsString(readBuff, readableBytes());
}

int Buffer::readBytes(std::vector<char> &data, uint32_t len)
{
  len = std::min(readableBytes(), len);
  // TODO
}

const char *Buffer::findCRLF() const
{
  char kCRLF[] = "\r\n";
  const char *crlf = std::search(readIndexPtr(), readIndexPtr() + writeIndex,
                                 kCRLF, kCRLF + 2);
  return crlf == (bufferPtr() + writeIndex) ? nullptr : crlf;
}

void Buffer::retrieveUntil(const char *end)
{
  if (readIndexPtr() > end)
  {
    std::cout << "error retrievaUntil" << std::endl;
    return;
  }
  if (end > (bufferPtr() + writeIndex))
  {
    std::cout << "error retrievaUntil" << std::endl;
    return;
  }
  updateReadIndex(end - readIndexPtr());
}