cmake_minimum_required(VERSION 2.8)

set(ROOT ../../)
set(MUDUO_LIB
    /home/hongyulin/C++/myserver/muduo/lib/)

set(http_SRCS
    http_parser.c
    httpparser.cpp
    httputil.cpp
    httprequest.cpp
    httpresponse.cpp
    httpdataparser.cpp
    ../stringutil.cpp)

include_directories(${ROOT} ../)
link_directories(${MUDUO_LIB})

add_library(http_net ${http_SRCS})
target_link_libraries(http_net muduo_base)

set_target_properties(http_net PROPERTIES COMPILE_FLAGS "-std=c++0x")
