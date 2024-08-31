cmake_minimum_required(VERSION 3.15)
project(RestApiService)

set(CMAKE_CXX_STANDARD 17)

# Find Boost and Beast
find_package(Boost REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})
include_directories(include)

add_executable(rest_api_service src/main.cpp src/rest_api_handler.cpp)

target_link_libraries(rest_api_service ${Boost_LIBRARIES} pqxx pq)