#include "TcpConnect.h"
using namespace yy;
using namespace std;

TcpConncet::TcpConncet(EventLoop *loop, SocketAddr &a, int fd) : loop(loop),
                                                                 addr(a),
                                                                 name(addr.toString()),
                                                                 event(new Channel(loop, fd)),
                                                                 socket(new Socket(fd)),
                                                                 state(Disconnected) {
  setNoDelay();
  loop->updateChannel(event.get());
  event->setReadCallback(std::bind(&TcpConncet::readEvent, this));
  event->setWriteCallback(std::bind(&TcpConncet::writeEvent, this));
  event->setErrorCallback(std::bind(&TcpConncet::errorEvent, this));
  event->setCloseCallback(std::bind(&TcpConncet::closeCallback, this));
}

TcpConncet::~TcpConncet() {
  event->disableAll();
  //  event->removeEvnet(shared_from_this()); TODO
}

void TcpConncet::setNoDelay() {
  socket->setTcpNoDelay();
}

void TcpConncet::shutDownWrite() {
  if (state == Connected) {
    state = Disconnecting;
    socket->shutDownWrite();
  }
}

void TcpConncet::readEvent() {
  int error = 0;
  int n = readBuffer.readFromIO(event->fd(), error);
  if (n > 0) {
    if (!!messageCallback) {
      messageCallback(shared_from_this(), readBuffer);
    }
  } else if (n == 0) {
    closeEvent();
  } else {
    std::cerr << "Error: TcpConnect read error" << std::to_string(error) << endl;
    closeEvent();
  }
}

void TcpConncet::closeEvent() {
  state = Disconnected;
  if (closeCallback) {
    closeCallback(shared_from_this());
  }
}

void TcpConncet::writeEvent() {
}