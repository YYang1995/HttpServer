cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        Thread.cpp
        ALog.cpp
        CountDownLatch.cpp
        )
add_library(my_base ${SOURCES})
target_link_libraries(my_base pthread)

file(GLOB HEADERS "*.h")

install(TARGETS my_base
        DESTINATION lib)

install(FILES ${HEADERS} DESTINATION include/muduo_practice/base)
