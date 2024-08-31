cmake_minimum_required(VERSION 3.15)

project(object-list-processor)

set(CMAKE_CXX_STANDARD 17)

set(PQXX_INCLUDE_DIR "/opt/goinfre/evangelm/homebrew/opt/libpqxx/include")
#set(PQXX_LIBRARY "/opt/goinfre/evangelm/homebrew/opt/libpqxx/lib/libpqxx.a")

include_directories(include)
include_directories(db)
include_directories(${PQXX_INCLUDE_DIR})

add_executable(object-list-processor
        src/main.cc
        db/postgres_database_manager.hpp
        db/base_database_manager.hpp
        include/object.hpp
)

#include_directories(${PQXX_INCLUDE_DIR})
#target_link_libraries(object-list-processor PRIVATE ${PQXX_LIBRARY})

# Use pkg-config to find libpqxx
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(PQXX REQUIRED libpqxx)

# Add the directory containing libpqxx to the linker search path
link_directories(/opt/goinfre/evangelm/homebrew/Cellar/libpqxx/7.9.2/lib)
target_link_libraries(object-list-processor PRIVATE pqxx)


# Include directories and link libraries
#include_directories(${PQXX_INCLUDE_DIRS})
#link_directories(${PQXX_LIBRARY_DIRS})
#target_link_libraries(object-list-processor PRIVATE ${PQXX_LIBRARIES})

