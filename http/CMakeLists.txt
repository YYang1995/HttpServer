cmake_minimum_required(VERSION 2.6)
project(http_server)

set(SOURCES
        HttpContext.cpp
        HttpRequest.cpp
        HttpResponse.cpp
        HttpServer.cpp
        )

add_library(my_http ${SOURCES})
target_link_libraries(my_http my_net)

file(GLOB HTTPS "*.h")

install(TARGETS my_http
        DESTINATION lib)

install(FILES ${HTTPS}
        DESTINATION include/http_server/http)