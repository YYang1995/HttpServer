cmake_minimum_required(VERSION 3.0)

set(SOURCES
        noncopyable.cpp
        )
add_library(my_base ${SOURCES})
file(GLOB HEADERS "*.h")

install(TARGETS my_base
        DESTINATION lib)

install(FILES ${HEADERS} DESTINATION include/muduo_practice/base)
