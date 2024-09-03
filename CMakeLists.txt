cmake_minimum_required(VERSION 3.15)
project(object-list-processor)

set(CMAKE_CXX_STANDARD 17)

# Find Boost and Beast
find_package(Boost)
find_package(PostgreSQL)
find_package(Threads)
find_package(CURL)

include_directories(${Boost_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})
include_directories(server/rest_api_service/include)
include_directories(server/db)
include_directories(.)
include_directories(server/rest_api_service/include)

add_executable(object-list-processor-server
        server/db/base_database_manager.hpp
        server/db/postgres_database_manager.hpp
        shared/src/models/object.cpp
        shared/include/models/object.hpp
        server/rest_api_service/src/controllers/object_controller.cpp
        server/rest_api_service/include/controllers/object_controller.hpp
        server/rest_api_service/src/serializers/object_serializer.cpp
        server/rest_api_service/include/serializers/object_serializer.hpp
        server/rest_api_service/src/services/object_service.cpp
        server/rest_api_service/include/services/object_service.hpp
        server/rest_api_service/src/context.cpp
        server/rest_api_service/include/context.hpp
        server/rest_api_service/src/main.cpp
        server/rest_api_service/src/router.cpp
        server/rest_api_service/include/router.hpp
        server/rest_api_service/src/server.cpp
        server/rest_api_service/include/server.hpp
        server/rest_api_service/include/aux/object_group_handler/object_group_handler.hpp
        server/rest_api_service/src/aux/object_group_handler/object_group_handler.cc
)

add_executable(object-list-processor-client
        shared/src/models/object.cpp
        shared/include/models/object.hpp
        client/src/main.cc
)

target_link_libraries(object-list-processor-server ${Boost_LIBRARIES} pqxx pq pthread)
target_link_libraries(object-list-processor-client curl)

#target_link_libraries(server PRIVATE shared)
