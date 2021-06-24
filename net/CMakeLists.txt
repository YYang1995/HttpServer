CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(muduo_practice)

set(SOURCES
        Channel.cpp
        EventLoop.cpp
        Poller.cpp
        EventLoopThread.cpp
        SocketOperation.cpp
        )
add_library(my_net ${SOURCES})
target_link_libraries(my_net pthread my_base)

file(GLOB HEADERS "*.h")

install(TARGETS my_net
        DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/muduo_practice/net)