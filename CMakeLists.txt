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
include_directories(src/server/rest_api_service/include)

add_executable(object-list-processor-server
        src/shared/src/models/object.cc
        src/shared/include/models/object.hpp
        src/server/rest_api_service/src/controllers/object_controller.cc
        src/server/rest_api_service/include/controllers/object_controller.hpp
        src/server/rest_api_service/src/serializers/object_serializer.cc
        src/server/rest_api_service/include/serializers/object_serializer.hpp
        src/server/rest_api_service/src/services/object_service.cc
        src/server/rest_api_service/include/services/object_service.hpp
        src/server/rest_api_service/src/context.cc
        src/server/rest_api_service/include/context.hpp
        src/server/rest_api_service/src/main.cc
        src/server/rest_api_service/src/router.cc
        src/server/rest_api_service/include/router.hpp
        src/server/rest_api_service/src/server.cc
        src/server/rest_api_service/include/server.hpp
        src/server/rest_api_service/include/aux/object_group_handler/object_group_handler.hpp
        src/server/rest_api_service/src/aux/object_group_handler/object_group_handler.cc
)

add_executable(object-list-processor-client
        src/shared/src/models/object.cc
        src/shared/include/models/object.hpp
        src/client/src/main.cc
)

target_link_libraries(object-list-processor-server ${Boost_LIBRARIES} pqxx pq pthread)
target_link_libraries(object-list-processor-client curl)
