cmake_minimum_required(VERSION 2.6)

set(SOURCES
        HttpContext.cpp
        HttpRequest.cpp
        HttpResponse.cpp
        HttpServer.cpp
        echo.cpp
        )

add_library(my_http ${SOURCES})
#target_link_libraries(my_http)

file(GLOB HTTPS "*.h")

install(TARGETS my_http
        DESTINATION lib)

install(FILES ${HTTPS}
        DESTINATION include/muduo_practice/http)