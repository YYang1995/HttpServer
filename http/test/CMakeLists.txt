cmake_minimum_required(VERSION 2.6)
project(http_test)

add_executable(contestTest HttpContextTest.cpp)
target_link_libraries(contestTest my_http my_net)
add_test(NAME contestTest COMMAND contestTest)

add_executable(EchoTest EchoTest.cpp)
target_link_libraries(EchoTest my_http my_net my_base)
add_test(NAME EchoTest COMMAND EchoTest)