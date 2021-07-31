cmake_minimum_required(VERSION 3.6)
project(muduo_practice_test)

add_executable(eventloopTest EventLoopTest.cpp)
target_link_libraries(eventloopTest my_net pthread)
add_test(NAME eventloopTest COMMAND eventloopTest)

#add_executable(tcpAcceptorTest TcpAcceptorTest.cpp)
#target_link_libraries(tcpAcceptorTest my_net pthread)
#add_test(NAME tcpAcceptorTest COMMAND tcpAcceptorTest)

add_executable(threadTest ThreadTest.cpp)
target_link_libraries(threadTest my_base pthread)
add_test(NAME threadTest COMMAND threadTest)

add_executable(EventLoopThreadTest EventLoopThreadTest.cpp)
target_link_libraries(EventLoopThreadTest my_net pthread)
add_test(NAME EventLoopThreadTest COMMAND EventLoopThreadTest)

ADD_EXECUTABLE(BufferTest BufferTest.cpp)
target_link_libraries(BufferTest my_net pthread)
add_test(NAME BufferTest COMMAND BufferTest)