cmake_minimum_required(VERSION 3.15)

project(object-list-processor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(/Users/evangelm/goinfre/homebrew/opt/libpqxx/include)

add_executable(object-list-processor
        src/main.cc
        db/postgres_database_manager.hpp
        db/base_database_manager.hpp
        include/object.hpp
)