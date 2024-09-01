cmake_minimum_required(VERSION 3.15)

project(object-list-processor-client)

set(CMAKE_CXX_STANDARD 17)

add_executable(object-list-processor-client
        src/main.cc
        ../shared/include/object.hpp
)

target_link_libraries(object-list-processor-client PRIVATE shared)
target_include_directories(object-list-processor-client PRIVATE ../shared/include)
