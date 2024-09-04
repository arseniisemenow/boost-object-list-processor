cmake_minimum_required(VERSION 3.15)
project(object-list-processor)

set(CMAKE_CXX_STANDARD 17)

# Find Boost and Beast
find_package(Boost)
find_package(PostgreSQL)
find_package(Threads)
find_package(CURL)

#include_directories(${Boost_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})
include_directories(src/server/rest_api_service/include)
include_directories(src/server/db)
include_directories(src)
include_directories(src/server/include)

add_executable(object-list-processor-server
        src/shared/src/models/object.cc
        src/shared/include/models/object.hpp
        src/server/src/controllers/object_controller.cc
        src/server/include/controllers/object_controller.hpp
        src/server/src/serializers/object_serializer.cc
        src/server/include/serializers/object_serializer.hpp
        src/server/src/services/object_service.cc
        src/server/include/services/object_service.hpp
        src/server/src/context.cc
        src/server/include/context.hpp
        src/server/src/main.cc
        src/server/src/router.cc
        src/server/include/router.hpp
        src/server/src/server.cc
        src/server/include/server.hpp
        src/server/include/aux/object_group_handler/object_group_handler.hpp
        src/server/src/aux/object_group_handler/object_group_handler.cc
)

add_executable(object-list-processor-client
        src/shared/src/models/object.cc
        src/shared/include/models/object.hpp
        src/client/src/main.cc
)

target_link_libraries(object-list-processor-server ${Boost_LIBRARIES} pqxx pq pthread)
target_link_libraries(object-list-processor-client curl)
