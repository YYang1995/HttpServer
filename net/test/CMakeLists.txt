cmake_minimum_required(VERSION 3.6)
project(muduo_practice_test)

add_executable(eventloopTest EventLoopTest.cpp)
target_link_libraries(eventloopTest my_net pthread)
add_test(NAME eventloopTest COMMAND eventloopTest)