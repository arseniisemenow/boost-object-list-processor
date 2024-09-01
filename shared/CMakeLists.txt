# shared/CMakeLists.txt

add_library(shared STATIC)
target_sources(shared PRIVATE
        include/object.hpp
)
target_include_directories(shared PUBLIC include)
