cmake_minimum_required(VERSION 3.15)
project(object-list-processor)

set(CMAKE_CXX_STANDARD 17)

# Find Boost and Beast
find_package(Boost REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})
include_directories(rest_api_service/include)
include_directories(db)

add_executable(server
        rest_api_service/src/main.cpp
        rest_api_service/src/rest_api_handler.cpp
        rest_api_service/include/session.hpp
)

target_link_libraries(server ${Boost_LIBRARIES} pqxx pq shared)

#target_link_libraries(server PRIVATE shared)
target_include_directories(server PRIVATE ../shared/include)