cmake_minimum_required(VERSION 3.15)
project(object-list-processor)

set(CMAKE_CXX_STANDARD 17)

# Find Boost and Beast
find_package(Boost REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS})
include_directories(rest_api_service/include)
include_directories(db)
include_directories(../shared)

add_executable(server
        db/base_database_manager.hpp
        db/postgres_database_manager.hpp
        ../shared/src/models/object.cpp
        ../shared/include/models/object.hpp
        rest_api_service/src/controllers/object_controller.cpp
        rest_api_service/include/controllers/object_controller.hpp
        rest_api_service/src/serializers/object_serializer.cpp
        rest_api_service/include/serializers/object_serializer.hpp
        rest_api_service/src/services/object_service.cpp
        rest_api_service/include/services/object_service.hpp
        rest_api_service/src/context.cpp
        rest_api_service/include/context.hpp
        rest_api_service/src/main.cpp
        rest_api_service/src/router.cpp
        rest_api_service/include/router.hpp
        rest_api_service/src/server.cpp
        rest_api_service/include/server.hpp
)

target_link_libraries(server ${Boost_LIBRARIES} pqxx pq shared)

#target_link_libraries(server PRIVATE shared)
target_include_directories(server PRIVATE ../shared/include)
