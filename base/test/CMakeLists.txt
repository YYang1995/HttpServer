cmake_minimum_required(VERSION 2.6)
project(base_test)

add_executable(threadTest ThreadTest.cpp)
target_link_libraries(threadTest my_base pthread)
add_test(NAME threadTest COMMAND threadTest)