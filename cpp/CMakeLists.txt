cmake_minimum_required(VERSION 3.16)
project(fetch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(fetch
    src/main.cpp
    src/logger.cpp
    src/qv_auth.cpp
    src/qv_query.cpp
    src/json_export.cpp
)

target_include_directories(fetch PRIVATE src)

if (MSVC)
    target_compile_options(fetch PRIVATE /W4 /EHsc)
else()
    target_compile_options(fetch PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (WIN32)
    target_link_libraries(fetch PRIVATE user32)
endif()
